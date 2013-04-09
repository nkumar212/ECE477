/*
 * ECE 477 Purdue University
 * Team 16: Project Minotaur Home Security Robot
 * Scott Stack, Neil Kumar, Jon Roose, John Hubberts
 *
 * This is the main file for the robot microcontroller code
 *
 */


//#include <stdio.h>
//#include <stdlib.h>
#include <p24Fxxxx.h>
#include "minotaur.h"


_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx1 & BKBUG_OFF)
//Use external oscillator -- use this for eval board but not final board
//_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_XT & FNOSC_PRI)
//Use internal oscillator instead of crystal
_CONFIG2( FCKSM_CSECME & OSCIOFNC_ON & POSCMOD_NONE & FNOSC_FRC)

//ISR function prototypes
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _U1RXInterrupt();
void __attribute__((__interrupt__,__auto_psv__)) _U1TXInterrupt();
void __attribute__((__interrupt__,__auto_psv__)) _T4Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _IC1Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _IC2Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _IC3Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _IC4Interrupt();


//flags
char SENSORS_READY = 0;    //1 when SENSOR adc scan is complete
char READY_TO_SEND = 1;    //One when there is space in the TX buffer
char READY_TO_REC = 0;
char PRINT = 0;
char I2C_READY_TO_SEND = 0;
char I2C_READY_TO_REC = 0;

//SENSOR range values
int SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5;

//The UART transmit and recieve data buffers
BUFFER TX_DATA_BUFFER;
BUFFER RX_DATA_BUFFER;

//The I2C transmit and receive buffers
BUFFER I2C_RX_BUFFER;
BUFFER I2C_TX_BUFFER;

//TIME BETWEEN PULSES FROM MOTOR ENCODERS
int ENCODER1[4];
int ENCODER2[4];
int ENCODER3[4];
int ENCODER4[4];

int LEFT_DISTANCE = 0; //distance left motor has traveled since start in ticks
int RIGHT_DISTANCE = 0;//distance right motor has traveled since start in ticks


int main(int argc, char** argv) {
    //char *toPrint = "Hello Neil";   //string of size 10
    char motor_direction = ' ';  //dictates the direction the robot will travel
                           //'F' - Forward
                           //'B' - Backwards
                           //'L' - Left
                           //'R' - Right
    unsigned char left_speed = 128;       //the speed of the left motor
    unsigned char right_speed = 128;      //the speed of the right motor

    char tempC;
    // Setup PortA IOs as digital outputs
    //TRISA = 0;

    //setup port B as digital output
    TRISE = 0;
    TRISB = 0x0FFF;

    //initialize peripherals
    initADC();
    initPWM();
    initTimer();
    initUART();
    //initInputCapture();

    //set up transmit data buffer
    TX_DATA_BUFFER.head = 0;
    TX_DATA_BUFFER.tail = 0;

    //set up recieve data buffer
    RX_DATA_BUFFER.head = 0;
    RX_DATA_BUFFER.tail = 0;

    //set duty cycle of OC3 to 50% to test
    //OC3RS = 0x007F;
    //OC4RS = 0x007F;

    //enable interrupts for the required molules
    IEC1bits.T4IE = 1;   //enable timer 3 interrupts
    IEC0bits.U1RXIE = 1; //enable UART Rx interrupts
    IFS0bits.U1RXIF = 0;
    IEC0bits.U1TXIE = 1; //enable UART Tx interrupts
    IEC0bits.AD1IE = 1;  //enable ADC interrupts
    IEC0bits.IC1IE = 1;  //enable input capture interrupts
    IEC0bits.IC2IE = 1;  //^
    IEC2bits.IC3IE = 1;  //^
    IEC2bits.IC4IE = 1;  //^

    // =====================================================================
    // =========================   MAIN LOOP   =============================
    //======================================================================
    while(1) {
        U1STAbits.UTXEN = 1;

        //LATE = 0x14;  //move motors forward
        //------------------------- ATD -------------------------------

        //If the SENSORs have recieved new values update the variables
        if (SENSORS_READY == 1) {
            
            //LATA = 1;
            AD1CON1bits.ASAM = 0;   //turn off sampling temporarily
            
            SENSOR4 = ADC1BUF0;
            SENSOR3 = ADC1BUF1;
            SENSOR2 = ADC1BUF2;
            SENSOR1 = ADC1BUF3;
            SENSOR5 = ADC1BUF4;

            AD1CON1bits.ASAM = 1;  //turn sampling back on
            SENSORS_READY = 0;
            
        }


        //------------------------- UART ----------------------------

        //TEST THE UART BY SENDING A MESSAGE WHEN TIMER INTERRUPTS     
        if (PRINT == 1) {
            //printInt(ENCODER1[0]);   //print the value of the first motor encoder
            //printString("hi\n\r");
            printString("Right ticks:");
            printInt(RIGHT_DISTANCE);
            printString("\n\r");
            PRINT = 0;
            LATB ^= 0x8000;
        }
        
        
        //If the UART module is ready to send a character, place the
        //next character in the TX buffer in the send register
        if (READY_TO_SEND == 1) {
            if (BUFF_status(&TX_DATA_BUFFER) != BUFF_EMPTY) {
                U1TXREG = BUFF_pop(&TX_DATA_BUFFER);
                READY_TO_SEND = 0;
            }
            
        }
        //If the UART module is ready to receive a character, place the char
        //in the receive buffer for later use
        if (READY_TO_REC == 1) {
            if (BUFF_status(&RX_DATA_BUFFER) != BUFF_FULL) {
                tempC = U1RXREG;
                BUFF_push(&RX_DATA_BUFFER, tempC);
                READY_TO_REC = 0;
                BUFF_push(&TX_DATA_BUFFER, tempC);  //TEMP --echo back char
            }
        }


        //(to read a byte from UART just use this...
        /*
        if (BUFF_status(&RX_DATA_BUFFER) != BUFF_EMPTY) {
            <BYTE> = BUFF_pop(&RX_DATA_BUFFER);
        }
        */

        //to write a byte to UART just use this...
        /*
        if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
            BUFF_push(&TX_DATA_BUFFER, <BYTE HERE>);
        }
        */


        //----------------------- I2C -------------------------------

        //I2C -if I2C is ready to receive a byte then receive the byte and
        //  place it in the receive buffer
        if (I2C_READY_TO_REC == 1) {
            if (BUFF_status(&I2C_RX_BUFFER) != BUFF_FULL) {
                tempC = read_i2c_byte();
                BUFF_push(&I2C_RX_BUFFER, tempC);
                I2C_READY_TO_REC = 0;
            }
        }


        //I2C - if any data to be sent, transmit it
        if (I2C_READY_TO_SEND == 1) {
            if (BUFF_status(&I2C_TX_BUFFER) != BUFF_EMPTY) {
                send_byte_i2c(BUFF_pop(&I2C_TX_BUFFER));
                I2C_READY_TO_SEND = 0;
            }
        }

        //(to read a byte from i2c just use this...
        /*
        if (BUFF_status(&I2C_RX_BUFFER) != BUFF_EMPTY) {
            <BYTE> = BUFF_pop(&I2C_RX_BUFFER);
        }
        */

        //to write a byte to i2c just use this...
        /*
        if (BUFF_status(&I2C_TX_BUFFER) != BUFF_FULL) {
            BUFF_push(&I2C_TX_BUFFER, <BYTE HERE>);
        }
        */


        //--------------------- MOTORS --------------------------

        //TEMP take the character received from UART and use it to determine
        //motor direction/speed
        if (BUFF_status(&RX_DATA_BUFFER) != BUFF_EMPTY) {
            tempC = BUFF_pop(&RX_DATA_BUFFER);
            switch(tempC) {
                case 'w':
                    motor_direction = 'F';
                    break;
                case 's':
                    motor_direction = 'B';
                    break;
                case 'a':
                    motor_direction = 'L';
                    break;
                case 'd':
                    motor_direction = 'R';
                    break;
                case ' ':
                    motor_direction = 'S';
                case '.':
                    left_speed += 2;
                    right_speed += 2;
                    break;
                case ',':
                    left_speed -= 2;
                    right_speed -= 2;
                    break;
            }
        }


        //Set the speed of the motors
        OC3RS = right_speed << 1; //set dutycycle of PWM based on POT val
        OC2RS = left_speed << 1;


        //adjust the direction of the motors
        switch(motor_direction) {
            case 'F':
                LATE = 0x14;
                break;
            case 'B':
                LATE = 0xA;
                break;
            case 'L':
                LATE = 0xC;
                break;
            case 'R':
                LATE = 0x12;
                break;
            case 'S':
                LATE = 0x00;
                break;
            default:
                break;
        }
         
        
        //light up LED if any sensor gets too close
        if(SENSOR1 > 800 | SENSOR4 > 800 | SENSOR3 > 800 | SENSOR2 > 800 | SENSOR5 > 800) {
            LATB |= 0x8000;
            //LATE = 0x00; //stop the robot
        }
        else {
            LATB &= 0x7FFF;
        }


    }
    
    return (0);
}






//The interrupt service routine for when the ADC conversions are complete
//for all of the SENSORs. It sets the SENSORS_READY flag.
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt() {
    IFS0bits.AD1IF = 0;     //clear intterupt flag
    //LATA = 0xF0;
    SENSORS_READY = 1;
    return;
}


//ISR for when a character is received from UART
void __attribute__((__interrupt__,__auto_psv__)) _U1RXInterrupt() {
    IFS0bits.U1RXIF = 0;    //clear interrupt flag
    //char c;

    //if framing error or parity error don't do anything
    if (U1STAbits.PERR == 1 || U1STAbits.FERR == 1) {
        return;
    }

    READY_TO_REC = 1;

    return;
}

//ISR for when TX buffer is empty for UART so that another byte can be sent
void __attribute__((__interrupt__,__auto_psv__)) _U1TXInterrupt() {
    IFS0bits.U1TXIF = 0;     //clear interrupt flag

    READY_TO_SEND = 1;

    return;
}

//ISR for when timer4 has expired. This means that no command has been received
//in the last 1.5 seconds and the robot should stop moving.

void __attribute__((__interrupt__,__auto_psv__)) _T4Interrupt() {
    IFS1bits.T4IF = 0;        //clear interrupt flag
    PRINT = 1;
    return;
}


//ISR for Input capture 1. Occurrs every 4 events (4 ticks of the encoder). So
//read all 4 timer values from the buffers and return
void __attribute__((__interrupt__,__auto_psv__)) _IC1Interrupt() {
    IFS0bits.IC1IF = 0;
    ENCODER1[0] = IC1BUF;
    ENCODER1[1] = IC1BUF;
    ENCODER1[2] = IC1BUF;
    ENCODER1[3] = IC1BUF;

    RIGHT_DISTANCE += 4;
}
//IC2
void __attribute__((__interrupt__,__auto_psv__)) _IC2Interrupt() {
    IFS0bits.IC2IF = 0;
    ENCODER2[0] = IC2BUF;
    ENCODER2[1] = IC2BUF;
    ENCODER2[2] = IC2BUF;
    ENCODER2[3] = IC2BUF;
}
//IC3
void __attribute__((__interrupt__,__auto_psv__)) _IC3Interrupt() {
    IFS2bits.IC3IF = 0;
    ENCODER3[0] = IC3BUF;
    ENCODER3[1] = IC3BUF;
    ENCODER3[2] = IC3BUF;
    ENCODER3[3] = IC3BUF;

    LEFT_DISTANCE += 4;
}
//IC4
void __attribute__((__interrupt__,__auto_psv__)) _IC4Interrupt() {
    IFS2bits.IC4IF = 0;
    ENCODER4[0] = IC4BUF;
    ENCODER4[1] = IC4BUF;
    ENCODER4[2] = IC4BUF;
    ENCODER4[3] = IC4BUF;
}

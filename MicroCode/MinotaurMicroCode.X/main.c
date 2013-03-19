/*
 * ECE 477 Purdue University
 * Team 16: Project Minotaur Home Security Robot
 * Scott Stack, Neil Kumar, Jon Roose, John Hubberts
 *
 * This is the main file for the robot microcontroller code
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <p24Fxxxx.h>
#include "minotaur.h"

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2)
//Use external oscillator -- use this for eval board but not final board
_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_XT & FNOSC_PRI)
//Use internal oscillator instead of crystal
//_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_NONE & FNOSC_FRC)

//ISR function prototypes
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _U2RXInterrupt();
void __attribute__((__interrupt__,__auto_psv__)) _U2TXInterrupt();
void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt();


//flags
int SENSORS_READY = 0;    //1 when SENSOR adc scan is complete
int READY_TO_SEND = 1;    //One when there is space in the TX buffer
int READY_TO_REC = 0;
int PRINT = 0;

char PREV_LAT = 0x00;
//SENSOR range values
int SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5;
BUFFER TX_DATA_BUFFER;
BUFFER RX_DATA_BUFFER;

void delay(void) {
    long i = 65535;
    while(i--)
        ;
}

int main(int argc, char** argv) {
    //char *toPrint = "Hello Neil";   //string of size 10
    char motor_direction = ' ';  //dictates the direction the robot will travel
                           //'F' - Forward
                           //'B' - Backwards
                           //'L' - Left
                           //'R' - Right
    char left_speed = 255;       //the speed of the left motor
    char right_speed = 255;      //the speed of the right motor

    char tempC;
    // Setup PortA IOs as digital outputs
    TRISA = 0;
    //AD1PCFG = 0xffff;

    //setup port B as digital output
    TRISE = 0;
    

    //initialize peripherals
    initADC();
    initPWM();
    initTimer();
    initUART();

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
    IEC0bits.T3IE = 1;   //enable timer 3 interrupts
    IEC1bits.U2RXIE = 1; //enable UART Rx interrupts
    IFS1bits.U2RXIF = 0;
    IEC1bits.U2TXIE = 1; //enable UART Tx interrupts
    IEC0bits.AD1IE = 1;  //enable ADC interrupts

    // =====================================================================
    // =========================   MAIN LOOP   =============================
    //======================================================================
    while(1) {
        U2STAbits.UTXEN = 1;
        
        //If the SENSORs have recieved new values update the variables
        if (SENSORS_READY == 1) {
            
            LATA = 1;
            AD1CON1bits.ASAM = 0;   //turn off sampling temporarily
            
            SENSOR1 = ADC1BUF0;
            SENSOR2 = ADC1BUF1;
            SENSOR3 = ADC1BUF2;
            SENSOR4 = ADC1BUF3;
            SENSOR5 = ADC1BUF4;

            AD1CON1bits.ASAM = 1;  //turn sampling back on
            SENSORS_READY = 0;
            
            

            OC3RS = SENSOR4 >> 2; //set dutycycle of PWM based on POT val
            OC4RS = SENSOR4 >> 2;
            //toPrint = intToString(SENSOR1, (toPrint+10));
            //
        }

        //TEST THE UART BY SENDING A MESSAGE WHEN TIMER INTERRUPTS
        
        if (PRINT == 1) {
            prInt(SENSOR4);
            printString("\n\r");
            PRINT = 0;
        }
        
        
        //If the UART module is ready to send a character, place the
        //next character in the TX buffer in the send register
        if (READY_TO_SEND == 1) {
            if (BUFF_status(&TX_DATA_BUFFER) != BUFF_EMPTY) {
                U2TXREG = BUFF_pop(&TX_DATA_BUFFER);
                READY_TO_SEND = 0;
            }
            
        }
        //If the UART module is ready to receive a character, place the char
        //in the receive buffer for later use
        if (READY_TO_REC == 1) {
            if (BUFF_status(&RX_DATA_BUFFER) != BUFF_FULL) {
                tempC = U2RXREG;
                BUFF_push(&RX_DATA_BUFFER, tempC);
                READY_TO_REC = 0;
                BUFF_push(&TX_DATA_BUFFER, tempC);
            }
        }
        //take the character received from UART and use it to determine motor direction
        if (BUFF_status(&RX_DATA_BUFFER) != BUFF_EMPTY) {
            motor_direction = BUFF_pop(&RX_DATA_BUFFER);
        }



        //adjust the direction of the motors
        switch(motor_direction) {
            case 'W':
                LATE = 0x14;
                break;
            case 'S':
                LATE = 0xA;
                break;
            case 'A':
                LATE = 0x12;
                break;
            case 'D':
                LATE = 0xC;
                break;
            case ' ':
                LATE = 0x00;
                break;
            default:
                break;
        }

    
        
        //light up LEDs based on ATD value
        if(SENSOR4 > 50) {
            LATA = 0x01;
        }
        if(SENSOR4 > 100){
            LATA = 0x03;
        }
        if(SENSOR4 > 200){
            LATA = 0x07;
        }
        if(SENSOR4 > 300){
            LATA = 0x0F;
        }
        if(SENSOR4 > 400)
        {
            LATA = 0x1F;
        }
        if(SENSOR4 > 500){
            LATA = 0x3F;
        }
        if(SENSOR4 > 600){
            LATA = 0x7F;
        }
        if(SENSOR4 > 1000){
            LATA = 0xFF;
        }
        
    }
    
    return (EXIT_SUCCESS);
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
void __attribute__((__interrupt__,__auto_psv__)) _U2RXInterrupt() {
    IFS1bits.U2RXIF = 0;    //clear interrupt flag
    //char c;

    //if framing error or parity error don't do anything
    if (U2STAbits.PERR == 1 || U2STAbits.FERR == 1) {
        return;
    }

    READY_TO_REC = 1;

    return;
}

//ISR for when TX buffer is empty for UART so that another byte can be sent
void __attribute__((__interrupt__,__auto_psv__)) _U2TXInterrupt() {
    IFS1bits.U2TXIF = 0;     //clear interrupt flag

    READY_TO_SEND = 1;

    return;
}

//ISR for when timer3 has expired. This means that no command has been received
//in the last 1.5 seconds and the robot should stop moving.
void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt() {
    IFS0bits.T3IF = 0;        //clear interrupt flag
    PRINT = 1;
    return;
}

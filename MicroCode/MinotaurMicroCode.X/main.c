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
//void __attribute__((__interrupt__,__auto_psv__)) _I2C1Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _U1RXInterrupt();
void __attribute__((__interrupt__,__auto_psv__)) _U1TXInterrupt();
void __attribute__((__interrupt__,__auto_psv__)) _T4Interrupt();
//void __attribute__((__interrupt__,__auto_psv__)) _IC1Interrupt();
//void __attribute__((__interrupt__,__auto_psv__)) _IC2Interrupt();
//void __attribute__((__interrupt__,__auto_psv__)) _IC3Interrupt();
//void __attribute__((__interrupt__,__auto_psv__)) _IC4Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _MI2C1Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt();

void wait();

//flags
char SENSORS_READY = 0;    	//1 when SENSOR adc scan is complete
char SENSOR_ENABLE = 0;         //enable or disable the proximity sensors
char SENSOR_TRIPPED = 0;
char READY_TO_SEND = 1;   	//One when there is space in the TX buffer
char READY_TO_REC = 0;
char PRINT = 0; 			//TEMP
char GET_BATT = 0;
char BATT_READY = 0;
char I2C_READY_TO_SEND = 0;
char I2C_READY_TO_REC = 0;
char TIMEOUT = 0; 			// if 1 then stop all motor movement b/c communication has been lost
char I2C_START = 0;			// if start sequence has been started, interrupt when 1 means start has finished
char I2C_RESTART = 0;		// 1 if restatrt sequence has been started
char I2C_STOP = 0;			// 1 if stop sequence has been started
char I2C_SEND_BYTE = 0;		// incremented for each byte sent (1 after byte 1 sending has begun
							// incremented to 2 when byte one has finished sending and been ACK'd
char I2C_RECV_BYTE = 0;		// same principle as above except for recieving
char I2C_ISR = 0;			// set when i2c interrupts
char I2C_ERROR = 0;                     // set when i2c interrupts but nothing is being sent/recieved

//SENSOR range values
int SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5;

//The UART transmit and recieve data buffers
BUFFER TX_DATA_BUFFER;
BUFFER RX_DATA_BUFFER;

//The I2C transmit and receive buffers
BUFFER I2C_RX_BUFFER;
BUFFER I2C_TX_BUFFER;

//control packet used for communication from atom board
controlData controlpacket;

//TIME BETWEEN PULSES FROM MOTOR ENCODERS
int ENCODER1[4];
int ENCODER2[4];
int ENCODER3[4];
int ENCODER4[4];
char PREV_ENCODER_RIGHT = 0;
char PREV_ENCODER_LEFT = 0;


int LEFT_TICKS = 0; //distance left motor has traveled since start in ticks
int RIGHT_TICKS = 0;//distance right motor has traveled since start in ticks


int main(int argc, char** argv) {
    unsigned char right_direction = 'S';  //S- stop, F - Forwards, B - Backwards
    unsigned char left_direction = 'S';
    unsigned char user_right_direction = 'S';  //S- stop, F - Forwards, B - Backwards
    unsigned char user_left_direction = 'S';

    //char motor_direction = ' '; //TEMP
    unsigned int left_speed = 0;       //the speed of the left motor
    unsigned int right_speed = 0;      //the speed of the right motor
    unsigned int user_left_speed = 0;       //the speed of the left motor
    unsigned int user_right_speed = 0;      //the speed of the right motor
    unsigned char battery_percentage = 100;

    //int right_distance = 0;//the distance that the right motor has traveled in cm
    //int left_distance = 0; //the distance that the left motor has traveled in cm

    unsigned char tempC = 0 ; //temporary char
    unsigned char tempC1, tempC2;
    unsigned char tempBuffC = 0;

    //setup port B as digital output
    TRISE = 0;
    TRISB = 0x0FFF;
    TRISD = 0xF00;  //enable port D pins (encoders) as inputs

    //initialize peripherals
    initADC();
    initPWM();
    initTimer();
    initUART();
    initInputCapture();
    i2c_init();

    //set up transmit data buffer
    TX_DATA_BUFFER.head = 0;
    TX_DATA_BUFFER.tail = 0;

    //set up recieve data buffer
    RX_DATA_BUFFER.head = 0;
    RX_DATA_BUFFER.tail = 0;

    //initialize the control packet
    controlpacket.bytesRecieved = 0;

    //enable interrupts for the required molules
    IEC1bits.MI2C1IE = 1;
    IEC1bits.T4IE = 1;   //enable timer 3 interrupts
    IEC0bits.T3IE = 1;
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

        
        //------------------------- ATD -------------------------------

        //If the SENSORs have recieved new values update the variables
        if (SENSORS_READY == 1) { 
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

        //TEMP -- TEST THE UART BY SENDING A MESSAGE WHEN TIMER INTERRUPTS
        if (PRINT == 1) {
            //printString("Right ticks:");
            //printInt(RIGHT_TICKS);
            //printString("\n\r");
            //printString("Left ticks:");
            //printInt(LEFT_TICKS);
            //printString("\n\r");
            printString("1: ");
            printInt(SENSOR1);
            printString("\n\r");
            printString("2: ");
            printInt(SENSOR2);
            printString("\n\r");
            printString("3: ");
            printInt(SENSOR3);
            printString("\n\r");
            printString("4: ");
            printInt(SENSOR4);
            printString("\n\r");
            printString("5: ");
            printInt(SENSOR5);
            printString("\n\r");


            PRINT = 0;
            //LATB ^= 0x8000;

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
                //BUFF_push(&TX_DATA_BUFFER, tempC);  //TEMP --echo back char
            }
        }


        //if there is a character available, pop it off and add it to the
        //control packet
        if (BUFF_status(&RX_DATA_BUFFER) != BUFF_EMPTY) {
            tempC = BUFF_pop(&RX_DATA_BUFFER);
            BUFF_push(&TX_DATA_BUFFER, tempC); ///TEMP
            switch(controlpacket.bytesRecieved) {
                case 0:
                    if (tempC == 0xAA) {
                        controlpacket.bytesRecieved = 1;
                    }
                    break;
                case 1:
                    controlpacket.sequence = tempC;
                    controlpacket.bytesRecieved += 1;
                    break;
                case 2:
                    controlpacket.command = tempC;
                    controlpacket.bytesRecieved += 1;
                    break;
                case 3:
                    controlpacket.data1 = tempC;
                    controlpacket.bytesRecieved += 1;
                    break;
                case 4:
                    controlpacket.data2 = tempC;
                    controlpacket.bytesRecieved += 1;
                    break;
                default:
                    break;
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

        //
        //if( /*READY TO READ FUEL VAL*/)
	//{
	//I2C_START = 0;
						
        //
        //(to read a byte from i2c just use this...
        /*
        if (BUFF_status(&I2C_RX_BUFFER) != BUFF_EMPTY) {
            <BYTE> = BUFF_pop(&I2C_RX_BUFFER);
        }
        */


        if(GET_BATT == 1)
        {
            I2C_START = i2c_start();
        }

        if( I2C_ISR == 1)
        {
            LATB ^= 0x8000;
            if( I2C_START == 1)
            {
                I2C_START = 0;
                I2C_SEND_BYTE += send_byte_i2c( 0xAA );		//send first byte: fuel gauge address in write mode
            }

            else if(I2C_SEND_BYTE == 1)
            {
                I2C_SEND_BYTE += send_byte_i2c( 0x02 ); 	//send first command byte StateOfCharge() command -- returns an unsigned int value 0-100%
            }

            else if(I2C_SEND_BYTE == 2)
            {
                I2C_SEND_BYTE += send_byte_i2c( 0x03 );		//send second command byte
            }

            else if(I2C_SEND_BYTE == 3)
            {
                I2C_SEND_BYTE = 0;
                I2C_RESTART += i2c_restart();				//after they ack second command byte send restart
            }

            else if(I2C_RESTART == 1)						//send 0xAB to designate read mode
            {
                I2C_RESTART = 0;
                I2C_SEND_BYTE += send_byte_i2c( 0xAB );
                if(I2C_SEND_BYTE == 1)
                {
                        I2C_SEND_BYTE = 4;
                }

            }

            else if(I2C_SEND_BYTE == 4)						//recieve 1 byte - unsigned int from 0 to 100 %
            {
                I2C_SEND_BYTE = 0;
                battery_percentage = read_i2c_byte_nack();
                I2C_RECV_BYTE = 1;
                BATT_READY = 1;
                GET_BATT = 0;
            }

            else if(I2C_RECV_BYTE == 1)					//send stop condition
            {
                I2C_RECV_BYTE = 0;
                //I2C_STOP += i2c_stop(); error
            }

            else if(I2C_STOP == 1)
            {
                I2C_STOP = 0;								//stop condition has completed clear stop i2c_stop flag
            }
            else
            {
                I2C_ERROR = 1;
            }
        }

			



        //--------------------- PROCESS CMD ---------------------
        if (controlpacket.bytesRecieved == 5) {  //if done receiving packet
            if (controlpacket.command == CMD_GET_SENSOR_DATA) {
                //Send all sensor data back


                //send IR data - 1 bit for each sensor (1 if tripped)
                if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_SENSOR);
                    tempBuffC = 0;
                    if (SENSOR1 > SEN_MAX)
                        tempBuffC |= 1;
                    if ((SENSOR2 > SEN_MAX) || (SENSOR4 < SEN_MIN))
                        tempBuffC |= 0x2;
                    if (SENSOR3 > SEN_MAX)
                        tempBuffC |= 0x4;
                    if ((SENSOR4 > SEN_MAX) || (SENSOR4 < SEN_MIN))
                        tempBuffC |= 0x8;
                    if ((SENSOR5 > SEN_MAX) || (SENSOR5 < SEN_MIN))
                        tempBuffC |= 0x10;
                    BUFF_push(&TX_DATA_BUFFER, tempBuffC);
                    BUFF_push(&TX_DATA_BUFFER, 0x00);
                }

                /*
                //first SENSOR1
                if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_SENSOR1);
                    BUFF_push(&TX_DATA_BUFFER, (char)(SENSOR1 >> 8));
                    BUFF_push(&TX_DATA_BUFFER, (char)SENSOR1);
                }
                 // SENSOR2
                if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_SENSOR2);
                    BUFF_push(&TX_DATA_BUFFER, (char)(SENSOR2 >> 8));
                    BUFF_push(&TX_DATA_BUFFER, (char)SENSOR2);
                }
                // SENSOR3
                if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_SENSOR3);
                    BUFF_push(&TX_DATA_BUFFER, (char)(SENSOR3 >> 8));
                    BUFF_push(&TX_DATA_BUFFER, (char)SENSOR3);
                }
                // SENSOR4
                if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_SENSOR4);
                    BUFF_push(&TX_DATA_BUFFER, (char)(SENSOR4 >> 8));
                    BUFF_push(&TX_DATA_BUFFER, (char)SENSOR4);
                }
                // SENSOR5
                if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_SENSOR5);
                    BUFF_push(&TX_DATA_BUFFER, (char)(SENSOR5 >> 8));
                    BUFF_push(&TX_DATA_BUFFER, (char)SENSOR5);
                }
                */
                // LEFT ENCODER
                if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_LEFT_ENCODER);
                    BUFF_push(&TX_DATA_BUFFER, (char)(LEFT_TICKS >> 8));
                    BUFF_push(&TX_DATA_BUFFER, (char)LEFT_TICKS);
                }
                // RIGHT_ENCODER
                if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_RIGHT_ENCODER);
                    BUFF_push(&TX_DATA_BUFFER, (char)(RIGHT_TICKS >> 8));
                    BUFF_push(&TX_DATA_BUFFER, (char)RIGHT_TICKS);
                }
                controlpacket.bytesRecieved = 0;
            }

            if (controlpacket.command == CMD_RIGHT_ENCODER) {
                BUFF_push(&TX_DATA_BUFFER, 0xAA);
                BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                BUFF_push(&TX_DATA_BUFFER, CMD_RIGHT_ENCODER);
                BUFF_push(&TX_DATA_BUFFER, (char)(RIGHT_TICKS >> 8));
                BUFF_push(&TX_DATA_BUFFER, (char)RIGHT_TICKS);
                controlpacket.bytesRecieved = 0;
            }

            if (controlpacket.command == CMD_LEFT_ENCODER) {
                BUFF_push(&TX_DATA_BUFFER, 0xAA);
                BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                BUFF_push(&TX_DATA_BUFFER, CMD_LEFT_ENCODER);
                BUFF_push(&TX_DATA_BUFFER, (char)(LEFT_TICKS >> 8));
                BUFF_push(&TX_DATA_BUFFER, (char)LEFT_TICKS);
                controlpacket.bytesRecieved = 0;
            }

            //battery level request
            if (controlpacket.command == CMD_BATTERY) {
                BUFF_push(&TX_DATA_BUFFER, 0xAA);
                BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                BUFF_push(&TX_DATA_BUFFER, CMD_BATTERY);
                BUFF_push(&TX_DATA_BUFFER, battery_percentage);
                BUFF_push(&TX_DATA_BUFFER, 0x00);
                controlpacket.bytesRecieved = 0;
            }


            //ir sensor
            if (controlpacket.command == CMD_SENSOR) {
                BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_SENSOR);
                    tempBuffC = 0;
                    if (SENSOR1 > SEN_MAX)
                        tempBuffC |= 1;
                    if ((SENSOR2 > SEN_MAX) || (SENSOR4 < SEN_MIN))
                        tempBuffC |= 0x2;
                    if (SENSOR3 > SEN_MAX)
                        tempBuffC |= 0x4;
                    if ((SENSOR4 > SEN_MAX) || (SENSOR4 < SEN_MIN))
                        tempBuffC |= 0x8;
                    if ((SENSOR5 > SEN_MAX) || (SENSOR5 < SEN_MIN))
                        tempBuffC |= 0x10;
                    BUFF_push(&TX_DATA_BUFFER, tempBuffC);
                    BUFF_push(&TX_DATA_BUFFER, 0x00);
            }
        }



        //--------------------- MOTORS --------------------------
        /*
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
        */

        //check to see if there is a new motor movement command
        if (controlpacket.bytesRecieved == 5 && controlpacket.command == CMD_MOTORS) {
            controlpacket.bytesRecieved = 0; //consume packet
            //TMR4 = 0; //reset the timeout timer b/c command has been received

            tempC1 = controlpacket.data1;
            if ((tempC1 & 0x80) == 0x80) {
                user_left_direction = 'B';
            } else if(tempC1 != 0){
                user_left_direction = 'F';
            } else {
                user_left_direction = 'S';
            }
            user_left_speed = (tempC1 & 0x7F) << 1;
            
            tempC2 = controlpacket.data2;
            if ((tempC2 & 0x80) == 0x80) {
                user_right_direction = 'B';
            } else if(tempC2 != 0){
                user_right_direction = 'F';
            } else {
                user_right_direction = 'S';
            }
            user_right_speed = (tempC2 & 0x7F) << 1;


            //send an ackknowledgement that we received the packet
            if (BUFF_status(&TX_DATA_BUFFER) != BUFF_FULL) {
                    BUFF_push(&TX_DATA_BUFFER, 0xAA);
                    BUFF_push(&TX_DATA_BUFFER, controlpacket.sequence);
                    BUFF_push(&TX_DATA_BUFFER, CMD_MOTORS);
                    BUFF_push(&TX_DATA_BUFFER, 0);
                    BUFF_push(&TX_DATA_BUFFER, 0);
            }
        }



        //TEMP -- adjust the direction of the motors
        /*
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
        */


        /* ENABLE FOR FINAL THING
        //if there is a timeout then stop all operation
        if (TIMEOUT == 1) {
            left_direction = 'S';
            right_direction = 'S';
        }
        */

        //enable or disable the sensors
        if(controlpacket.bytesRecieved == 5 && controlpacket.command == CMD_ENABLE_SENSORS) {
            SENSOR_ENABLE = controlpacket.data1;
        }

        if(controlpacket.bytesRecieved == 5 && controlpacket.command == CMD_AUTONOMOUS_MODE) {
            controlpacket.bytesRecieved = 0;
            if (controlpacket.data1 == 1) {
                user_right_speed = 0xFF;
                user_left_speed = 0xFF;
                user_left_direction = 'F';
                user_right_direction = 'F';
                SENSOR_ENABLE = 1;
            } else {
                user_right_speed = 0x00;
                user_left_speed = 0x00;
                user_left_direction = 'S';
                user_right_direction = 'S';
                SENSOR_ENABLE = 0;
            }
        }




        //Obstacle avoidance
        SENSOR_TRIPPED = 0;
        //if fron senter sensor senses farther than the floor, there is a drop
        //off and back up for a bit and to the right
        
        if (SENSOR_ENABLE && (SENSOR2 > SEN_MAX)) {
            right_speed = 0xFF;
            left_speed = 0xFF;
            right_direction = 'B';
            left_direction = 'F';
            SENSOR_TRIPPED = 1;
        }

        //same for back sensors
        //if (SENSOR_ENABLE && ((SENSOR4 < SEN_MIN) ||(SENSOR4 > 1020))) {
        if (SENSOR_ENABLE && (SENSOR4 > SEN_MAX)) {
            right_speed = 0xFF;
            left_speed = 0xFF;
            right_direction = 'F';
            left_direction = 'F';
            SENSOR_TRIPPED = 1;
        }
        //if (SENSOR_ENABLE && ((SENSOR5 < SEN_MIN) || (SENSOR5 > 1020))) {
        if (SENSOR_ENABLE && (SENSOR5 > SEN_MAX)) {
            right_speed = 0xFF;
            left_speed = 0xFF;
            right_direction = 'F';
            left_direction = 'F';
            SENSOR_TRIPPED = 1;
            //wait();
        }

        
        //front side sensors
        if (SENSOR_ENABLE && (SENSOR1 > SEN_MAX && SENSOR3 > SEN_MAX)) {
            right_speed = 0x10;
            left_speed = 0xFF;
            right_direction = 'B';
            left_direction = 'B';
            SENSOR_TRIPPED = 1;
            //wait();  //wait for robot to turn a bit
        }
        //if the side sensors get too close, turn the opposite way for a bit
        else if (SENSOR_ENABLE && (SENSOR1 > SEN_MAX)) { //left sensor
            right_speed = 0xFF;
            left_speed = 0xFF;
            right_direction = 'F';
            left_direction = 'B';
            SENSOR_TRIPPED = 1;
            //wait();  //wait for robot to turn a bit
        }
        else if (SENSOR_ENABLE && (SENSOR3 > SEN_MAX)) { //right sensor
            right_speed = 0xFF;
            left_speed = 0xFF;
            right_direction = 'B';
            left_direction = 'F';
            SENSOR_TRIPPED = 1;
            //wait();  //wait for robot to turn a bit
        }

        
        //if a sensor has not been tripped use the users speed/direction
        if (SENSOR_TRIPPED != 1) {
            right_speed = user_right_speed;
            right_direction = user_right_direction;
            left_speed = user_left_speed;
            left_direction = user_left_direction;
        }
        

        //Set the speed of the motors
        OC3RS = (right_speed << 1) & 0x1FF; //set dutycycle of PWM for motor speed
        OC2RS = (left_speed << 1) & 0x1FF;

        LATE = 0;
        //set direction of motors
        switch(left_direction) {
            case 'F':
                LATE |= 0x02;
                break;
            case 'B':
                LATE |= 0x04;
                break;
            default:
                LATE &= ~0x06;
                break;
        }
        switch(right_direction) {
            case 'F':
                LATE |= 0x08;
                break;
            case 'B':
                LATE |= 0x10;
                break;
            default:
                LATE &= ~0x18;
                break;
        }



        if (controlpacket.bytesRecieved == 5) {
            controlpacket.bytesRecieved = 0;
        }

       

    } //end while
    
    return (0);
}


/*********************************************************************

	Interrupt Service Routines

*********************************************************************/

/* 	ISR for i2c: interrupt is set on completion of these evets:

		-start conditiion
		-stop condition
		-data transfer byte transmitted/recieved
		-ACK/NACK transmit
		-Repeated Start
		-Bus Collision Event
*/
void __attribute__((__interrupt__,__auto_psv__)) _MI2C1Interrupt() {
    IFS1bits.MI2C1IF = 0;
    I2C_ISR = 1;
    return;
}	




//The interrupt service routine for when the ADC conversions are complete
//for all of the SENSORs. It sets the SENSORS_READY flag.
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt() {
    IFS0bits.AD1IF = 0;     //clear intterupt flag
    SENSORS_READY = 1;
    return;
}


//ISR for when a character is received from UART
void __attribute__((__interrupt__,__auto_psv__)) _U1RXInterrupt() {
    IFS0bits.U1RXIF = 0;    //clear interrupt flag

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
    TIMEOUT = 1;
    GET_BATT = 1;
    return;
}


//Motor encoder code. Keeps trac of the number of ticks (can be a negative number)
//SEE ->>  http://en.wikipedia.org/wiki/Rotary_encoder  - Incremental rotary encoder section
void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt() {
    unsigned char ch1 = PORTDbits.RD10 << 4; //current value of ch1 pin
    unsigned char ch2 = PORTDbits.RD11; //current value of ch2 pin
    unsigned char currentstate = ch1 | ch2;


    //ENCODER3[0] = IC3BUF;

    switch(PREV_ENCODER_LEFT) {
        case 0x00:
            if(currentstate == 0x01) {
                PREV_ENCODER_LEFT = 0x01;
                LEFT_TICKS += 1;
            } else if (currentstate == 0x10) {
                PREV_ENCODER_LEFT = 0x10;
                LEFT_TICKS -= 1;
            }
            break;
        case 0x01:
            if(currentstate == 0x00) {
                PREV_ENCODER_LEFT = 0x00;
            } else if (currentstate == 0x11) {
                PREV_ENCODER_LEFT = 0x11;
            }
            break;
        case 0x11:
            if (currentstate == 0x10) {
                PREV_ENCODER_LEFT = 0x10;
            } else if (currentstate == 0x01) {
                PREV_ENCODER_LEFT = 0x01;
            }
            break;
        case 0x10:
            if (currentstate == 0x00) {
                PREV_ENCODER_LEFT = 0x00;
            } else if (currentstate == 0x11) {
                PREV_ENCODER_LEFT = 0x11;
            }
            break;
        default:
            break;
    }


    ch1 = PORTDbits.RD8 << 4; //current value of ch1 pin
    ch2 = PORTDbits.RD9; //current value of ch2 pin.
    currentstate = ch1 | ch2;


    switch(PREV_ENCODER_RIGHT) {
        case 0x00:
            if(currentstate == 0x01) {
                RIGHT_TICKS += 1;
                PREV_ENCODER_RIGHT = 0x01; //at this point one full phase has gone by
            } else if (currentstate == 0x10) {
                RIGHT_TICKS -= 1;
                PREV_ENCODER_RIGHT = 0x10; //at this point one full phase has gone by
            }
            break;
        case 0x01:
            if(currentstate == 0x00) {
                PREV_ENCODER_RIGHT = 0x00;
            } else if (currentstate == 0x11) {
                PREV_ENCODER_RIGHT = 0x11;
            }
            break;
        case 0x11:
            if (currentstate == 0x10) {
                PREV_ENCODER_RIGHT = 0x10;
            } else if (currentstate == 0x01) {
                PREV_ENCODER_RIGHT = 0x01;
            }
            break;
        case 0x10:
            if (currentstate == 0x00) {
                PREV_ENCODER_RIGHT = 0x00;
            } else if (currentstate == 0x11) {
                PREV_ENCODER_RIGHT = 0x11;
            }
        default:
            break;

    }
    IFS0bits.T3IF = 0;

}


//wait used to redirect the robot when it senses an object
void wait() {
    unsigned int i;
    for (i=0;i<10000;i++);
    return;
}

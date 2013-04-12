

//#include<stdio.h>
#include<string.h>
//#include<stdlib.h>
#include <p24Fxxxx.h>
#include "minotaur.h"

/********************************
 *          i2c functions
 */

void i2c_init()
{
    int BRG = 100;
    int temp;

    //clock divider
    I2C1BRG = BRG;
    I2C1CONbits.I2CEN = 0;      //Disable i2c mode
    I2C1CONbits.DISSLW = 1;     //Disable slew rate control
    IFS1bits.MI2C1IF = 0;       //Clear Interrupt
    I2C1CONbits.I2CEN = 1;      //Enable i2c mode

    temp = I2C1RCV;              //read buffer to clear buffer full

    reset_i2c_bus();            //set bus to idle;


}
/*******************************
 *
 *      i2c Start Bit
 * returns a one to to designate that a start condition has been initiatied (set i2c_START flag)
 *
 ******************************/
int i2c_start()
{
    I2C1CONbits.ACKDT = 0;      //Reset previous ACK
    I2C1CONbits.SEN = 1;        //Initiate Start Condition
	Nop();

    //Start bit is cleared automatically;
    //wait for automatic clear

	return 1;	
}


/******************************************
 *
 *          Sends Reset bit
 * returns one to designate that we are in a RESTART Condition (set restart flag)
 *
******************************************/
int i2c_restart()
{

    I2C1CONbits.RSEN = 1;
    Nop();

	return 1;

}

/**********************************
 *
 *          Resets i2c bus
 *
 * *******************************/
void i2c_stop(void)
{

    I2C1CONbits.PEN=1;

}

/***********************************
 *
 *        send byte: loads tx register to send and return 1 to set the BYTE_SENDING FLAG
 *
 *
 ***********************************/
int send_byte_i2c(char data)
{


    while(I2C1STATbits.TBF){}
    IFS1bits.MI2C1IF = 0;           //Clear Interrupt
    I2C1TRN = data;                 //Load outgoing data byte

    return 1;
}

/********************************************
 *     i2c_read_set: set master to read ready so byte can be recieved. will be interrupt when byte has been recieved. 
 *******************************************/

char i2c_read_set(void)
{

    //set i2c to recieve
    I2C1CONbits.RCEN = 1;

    return 1;

}


/*********************************************
 *              Read byte with ACK
 *
 *
 ********************************************/
char read_i2c_byte_ack(void)
{
		
    char data = 0;

    //get data from reg
    data = I2C1RCV;

		//set ACK sequence to send ACK
		I2C1CONbits.ACKDT = 0;

    //start ACK sequence
    I2C1CONbits.ACKEN = 1;

    return data;

}

/**********************************************
*							Read byte with NACK (used to recieve last byte of sequence, else use other (w/ ACK))
*
***********************************************/

char read_i2c_byte_nack(void)
{

		char data = 0;
	
		//get data from reg
		data = I2C1RCV;

		//set ACK sequence to send NACK
		I2C1CONbits.ACKDT = 1;
	
		//start ACK sequence;
		I2C1CONbits.ACKEN = 1;

		return data;
}



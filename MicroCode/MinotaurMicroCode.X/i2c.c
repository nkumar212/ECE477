

//#include<stdio.h>
#include<string.h>
//#include<stdlib.h>
#include <p24Fxxxx.h>
#include "minotaur.h"

/********************************
 *          i2c functions
 */

//NEIL -- interrupts need to be initialized for both transmit and receive.
//        If its an option, interrupt after every byte is received and after
//        every byte is transmitted (i.e. not after it receives 4 bytes or
//        something...idk if this is an option tho)
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
void reset_i2c_bus()
{
    int x = 0;

    //begin stop bit

    I2C1CONbits.PEN=1;

    //wait for stop bit to clear
    while(I2C1CONbits.PEN)
    {
        x++;
        if(x>20) break;
    }

    I2C1CONbits.RCEN = 0;
    IFS1bits.MI2C1IF = 0;           //Clear interrupt
    I2C1STATbits.IWCOL = 0;
    I2C1STATbits.BCL = 0;

}

/***********************************
 *
 *        send byte: input integer and returns 0 if successfull
 *
 ***********************************/
//NEIL -- this should basically just put the char into the transmit buffer
//        and send it. Put the error checking in the interrupt service routine
int send_byte_i2c(char data)
{
    int i;

    while(I2C1STATbits.TBF){}
    IFS1bits.MI2C1IF = 0;           //Clear Interrupt
    I2C1TRN = data;                 //Load outgoing data byte

    return 1;
}

/********************************************
 *              read byte from i2c but no ACK after
 *******************************************/

char read_i2c()
{

    int i = 0;
    char data = 0;

    //set i2c to recieve
    I2C1CONbits.RCEN = 1;

    //if no response break
    while(!I2C1STATbits.RBF)
    {
        i++;
        if(i>2000) break;
    }

    //get data from I2CRCV reg
    data = I2C1RCV;

    return data;

}


/*********************************************
 *              Read byte with ACK
 *
 *
 ********************************************/
//NEIL -- this needs to just read the byte from the register and return it
//       no waiting to see if successful
char read_i2c_byte()
{
    int i = 0;
    char data = 0;

    //set i2c to recieve
    I2C1CONbits.RCEN = 1;

    //break if no response
    while(!I2C1STATbits.RBF)
    {

        i++;
        if(i > 2000) break;

    }

    //get data from reg

    data = I2C1RCV;

    //set ACK to high
    I2C1CONbits.ACKEN = 1;

    //delay
    //delay(10);

    //return
    return data;

}


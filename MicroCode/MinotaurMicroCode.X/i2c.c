

#include<stdio.h>
#include<string.h>
#include<stdlib.h>



/********************************
 *          i2c functions
 */


void i2c_init()
{

    int temp;


    //clock divider
    I2C1BRG = BRG;
    I2C1CONbits.I2CEN = 0;      //Disable i2c mode
    I2C1CONbits.DISSLW = 1;     //Disable slew rate control
    IFS1bits.MI2C1IF = 0;       //Clear Interrupt
    I2C1CONbits.I2CEN = 1;      //Enable i2c mode

    temp = I2CRCV;              //read buffer to clear buffer full

    reset_i2c_bus();            //set bus to idle;


}
/*******************************
 *
 *      i2c Start Bit
 *
 ******************************/


void i2c_start()
{

    int x = 0;
    I2C1CONbits.ACKDT = 0;      //Reset previous ACK
    delay(10);
    I2C1CONbits.SEN = 1;        //Initiate Start Condition
    Nop();

    //Start bit is cleared automatically;
    //wait for automatic clear

    while(I2C1CONbits.SEN)
    {
        delay(1);
        x++;
        if(x > 20)
        {
            break;
        }
    }

    delay(2);

}


/******************************************
 *
 *          Sends Reset bit
 *
******************************************/

void i2c_restart()
{

    int x = 0;

    I2C1CONbits.RSEN = 1;
    Nop();

    while(I2C1CONbits.RSEN)
    {
        delay(1);
        x++;
        if(x > 20) break;
    }

    delay(2);

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
        delay(1)
        x++;
        if(x>20) break;
    }

    I2C1CONbits.RCEN = 0;
    IFS1bits.MI2C1IF = 0;           //Clear interrupt
    I2C1STATbits.IWCOL = 0;
    I2C1STATbits.BCL = 0;
    delay(10);

}
/***********************************
 *
 *        send byte: input integer and returns 0 if successfull
 *
 ***********************************/

char send_byte_i2c(int data)
{

    int i;

    while(I2C1STATbits.TBF){}
    IFS1bits.MI2C1IF = 0;           //Clear Interrupt
    I2CTRN = data;                  //Load outgoing data byte

    //wait for it to transmit

    for(i = 0; i<500; i++)
    {

        if(!I2C1STATbits.TRSTAT) break;
        delay(1);
    }

    if(i==500){
        return(1);
    }

    //check for NACK from slave
    if(I2C1STATbits.ACKSTAT == 1)
    {

        reset_i2c_bus();
        return(1);

    }

    delay(2);
    return(0);
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
    data = I2CRCV;

    return data;

}


/*********************************************
 *              Read byte with ACK
 *
 *
 ********************************************/

char read_i2c_wbyte()
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

    data = I2CRCV;

    //set ACK to high
    I2C1CONbits.ACKEN = 1;

    //delay
    delay(10);

    //return
    return data;

}

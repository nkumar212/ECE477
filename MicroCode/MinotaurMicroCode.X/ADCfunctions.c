/*
 * File:   main.c
 *
 * Created on February 9, 2010, 10:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24Fxxxx.h>
#include "minotaur.h"

/*
 *
 */

//Intialize the ADC to grab the values from all 5 IR sensors then interrupt
//when it is done
void initADC() {
    //set AN0,1,2,3,4 as analog input for testing with explorer 16 board
    //AD1PCFG = 0xFFE0;

    //set AN2,AN3,AN4,AN5, and AN9 as analog input
    AD1PCFG = 0xFDC3;
    AD1CHS = 0;
    //AD1PCFG = 0xFFFE; //only turn on AN0 as analog input

    //turn on ADC -- Integer mode -- Internal counter ends sampling and starts
    //conversion
    AD1CON1 = 0x80E6;

    //use external vref+/- -- scan inputs enable -- buffer configured as 2 8-bit
    //buffers -- interrupt after 5 conversions
    //AD1CON2 = 0x8414
    AD1CON2 = 0x0414; //same as above but use VDD/VSS for reference Voltage

    //TAD = 128 * (CLK/2 PERIOD)
    //AUTOSAMPLE 31 * TAD  = sample about every 1ms
    AD1CON3 = 0x1FFF;

    //select AN 0,1,2,3, and 4 for scan (For Explorer 16 test)
    //AD1CSSL = 0x001F;

    //select AN 2,3,4,5, and 9 for scan
    AD1CSSL = 0x023C;

    
    
    //TRISBbits.TRISB0 = 1;
    

}


//will get the sensor range from a sensor
//THIS IS NOT USED IN THE FINAL CODE - SCANNING WITH INTERRUPTS IS USED INSTEAD
long getIrSensorRange(char ID) {
    long Result;
    while(!AD1CON1bits.DONE);
    Result = (long) ADC1BUF0;

    return Result;
}


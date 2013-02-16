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
    //set AN2,AN3,AN4,AN5, and AN9 as analog input
    AD1PCFG = 0x023C;
    //AD1PCFG = 0xFFFE; //only turn on AN0 as analog input

    //turn on ADC -- Integer mode -- Internal counter ends sampling and starts
    //conversion
    AD1CON1 = 0x80E4;

    //use external vref+/- -- scan inputs enable -- buffer configured as 2 8-bit
    //buffers -- interrupt after 5 conversions
    AD1CON2 = 0x6410;
    //AD1CON2 = 0x0410 //same as above but use VDD/VSS for reference Voltage

    //TAD = 128 * (CLK/2 PERIOD)
    //AUTOSAMPLE 31 * TAD  = sample about every 1ms
    AD1CON3 = 0x1FFF;

    //select AN 2,3,4,5, and 9 for scan
    AD1CSSL = 0x023C;

    AD1CHS = 0;
    
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


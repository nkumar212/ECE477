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


void initADC() {
    AD1CON1 = 0x80E4;
    AD1CON2 = 0;
    AD1CON3 = 0x1F05;

    TRISBbits.TRISB0 = 1;
    AD1PCFG = 0xFFFE;

}


long getIrSensorRange(char ID) {
    long Result;
    while(!AD1CON1bits.DONE);
    Result = (long) ADC1BUF0;

    return Result;
}

int main_test(int argc, char** argv) {
    int counter;
    long temp;
    TRISA = 0;

    // Setup PortA IOs as digital
    AD1PCFG = 0xffff;

    initADC();

    while(1) {

        temp = getIrSensorRange(1);
        if(temp > 50) {
            LATA = 0x01;
        }
        if(temp > 100){
            LATA = 0x03;
        }
        if(temp > 200){
            LATA = 0x07;
        }
        if(temp > 300){
            LATA = 0x0F;
        }
        if(temp > 400)
        {
            LATA = 0x1F;
        }
        if(temp > 500){
            LATA = 0x3F;
        }
        if(temp > 600){
            LATA = 0x7F;
        }
        if(temp > 700){
            LATA = 0xFF;
        }
        delay();

    }
    return (EXIT_SUCCESS);
}


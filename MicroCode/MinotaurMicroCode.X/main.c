/* 
 * File:   main.c
 *
 * The main file for the minotaur robot microcontroller code
 * 
 * Created on February 9, 2010, 10:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24Fxxxx.h>
#include "minotaur.h"

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2)
//Use external oscillator -- use this for eval board but not final board
_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_XT & FNOSC_PRI)
//Use internal oscillator instead of cristal
//_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_NONE & FNOSC_FRC)

//function prototypes
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt();

//flags
int SENSORS_READY = 0;    //1 when sensor adc scan is complete


void delay(void) {
    long i = 65535;
    while(i--)
        ;
}

int main(int argc, char** argv) {
    //sensor range values
    int sensor1, sensor2, sensor3, sensor4, sensor5;
    TRISA = 0;

    // Setup PortA IOs as digital
    AD1PCFG = 0xffff;

    initADC();

    //infinite polling loop
    while(1) {

        if (SENSORS_READY) {
            AD1CON1bits.ASAM = 0;   //turn off sampling temporarily
            //if currently writing to <8:F> get data from <0:7>
            if (AD1CON2bits.BUFS == 1) {
                sensor1 = ADC1BUF0;
                sensor2 = ADC1BUF1;
                sensor3 = ADC1BUF2;
                sensor4 = ADC1BUF3;
                sensor5 = ADC1BUF4;
            }
            else {
                sensor1 = ADC1BUF8;
                sensor2 = ADC1BUF9;
                sensor3 = ADC1BUFA;
                sensor4 = ADC1BUFB;
                sensor5 = ADC1BUFC;
            }
            AD1CON1bits.ASAM = 1;  //turn sampling back on
        }


        //sensor1 = getIrSensorRange(1);
        if(sensor1 > 50) {
            LATA = 0x01;
        }
        if(sensor1 > 100){
            LATA = 0x03;
        }
        if(sensor1 > 200){
            LATA = 0x07;
        }
        if(sensor1 > 300){
            LATA = 0x0F;
        }
        if(sensor1 > 400)
        {
            LATA = 0x1F;
        }
        if(sensor1 > 500){
            LATA = 0x3F;
        }
        if(sensor1 > 600){
            LATA = 0x7F;
        }
        if(sensor1 > 700){
            LATA = 0xFF;
        }
        delay();
    }
    
    return (EXIT_SUCCESS);
}

//The interrupt service routine for when the ADC conversions are complete
//for all of the sensors. It sets the SENSORS_READY flag.
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt() {
    SENSORS_READY = 1;
    return;
}

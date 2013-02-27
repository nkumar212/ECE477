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

//function prototypes
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt();
void __attribute__((__interrupt__,__auto_psv__)) _U1RXInterrupt();
void __attribute__((__interrupt__,__auto_psv__)) _U1TXInterrupt();
void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt();


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

    // Setup PortA IOs as digital outputs
    TRISA = 0;
    AD1PCFG = 0xffff;

    //initialize peripherals
    initADC();
    initPWM();

    //set duty cycle of OC3 to 50% to test
    //OC3RS = 0x007F;
    //OC4RS = 0x007F;

    //enable interrupts for the required molules
    IEC0bits.T3IE = 1;   //enable timer 3 interrupts
    IEC0bits.U1RXIE = 1; //enable UART Rx interrupts
    IEC0bits.U1TXIE = 1; //enable UART Tx interrupts
    IEC0bits.AD1IE = 1;  //enable ADC interrupts

    // =====================================================================
    // =========================   MAIN LOOP   =============================
    //======================================================================
    while(1) {

        //If the sensors have recieved new values update the variables
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

        //light up LEDs based on ATD value
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

//ISR for when a character is received from UART
void __attribute__((__interrupt__,__auto_psv__)) _U1RXInterrupt() {
    return;
}

//ISR for when TX buffer is empty for UART so that another byte can be sent
void __attribute__((__interrupt__,__auto_psv__)) _U1TXInterrupt() {
    return;
}

//ISR for when timer3 has expired. This means that no command has been received
//in the last 1.5 seconds and the robot should stop moving.
void __attribute__((__interrupt__,__auto_psv__)) _T3Interrupt() {
    return;
}

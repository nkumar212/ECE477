/*
 * ECE 477 Purdue University
 * Team 16: Project Minotaur Home Security Robot
 * Scott Stack, Neil Kumar, Jon Roose, John Hubberts
 *
 * This file provides functions dealing with PWM and Timer module functionality
 *
 */

//#include <stdio.h>
//#include <stdlib.h>
#include <p24Fxxxx.h>
#include "minotaur.h"


//Initializes the PWM module to use OC3 and OC4 to control the speed of the
//motors.
void initPWM() {
    //set Timer 2 period to be about 15ms
    PR2 = 0x01FF;

    //set initial duty cycle to 0% (use OC3RS to set duty cycle in future code)
    OC3RS = 0x0000;
    OC3R = 0x0000;
    
    OC2RS = 0x0000;
    OC2R = 0x0000;

    //configure OC3 and OC4 to PWM mode -- no fault detection -- sleep on CPU
    //sleep -- use timer 2
    OC3CON = 0x2006;
    OC2CON = 0x2006;

    //enable Timer 2 to start PWM
    //set prescalar to 256
    T2CON = 0x8030;

    return;
}

//Initialize timer 3 as a timeout timer. If no command is received when the
//timer expires, stop moving the robot. Reset the timer when a command is
//received.

void initTimer() {
    //set timer to expire afer 1.5 seconds
    PR4 = 0x5B8D;
    T4CON = 0x8030; //enable timer and set prescalar to 256


    return;
}

void initInputCapture() {
    T3CONbits.TON = 1; //timer 3 on with no prescalar (FOSC/2) = 8MHz

    //IC1
    IC1CONbits.ICTMR = 0; //use timer 3
    IC1CONbits.ICI = 0x3; //interrupt every 4th capture
    IC1CONbits.ICM = 0x3; //capture every rising edge


    //IC2
    IC2CONbits.ICTMR = 0; //use timer 3
    IC2CONbits.ICI = 0x3; //interrupt every 4th capture
    IC2CONbits.ICM = 0x3; //capture every rising edge

    //IC3
    IC3CONbits.ICTMR = 0; //use timer 3
    IC3CONbits.ICI = 0x3; //interrupt every 4th capture
    IC3CONbits.ICM = 0x3; //capture every rising edge

    //IC4
    IC4CONbits.ICTMR = 0; //use timer 3
    IC4CONbits.ICI = 0x3; //interrupt every 4th capture
    IC4CONbits.ICM = 0x3; //capture every rising edge

}




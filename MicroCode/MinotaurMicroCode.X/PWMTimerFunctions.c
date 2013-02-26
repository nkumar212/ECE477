/*
 * ECE 477 Purdue University
 * Team 16: Project Minotaur Home Security Robot
 *
 *
 * This file provides functions dealing with PWM and Timer module functionality
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24Fxxxx.h>
#include "minotaur.h"


void initPWM() {
    //set Timer 2 period to be about 15ms
    PR2 = 0x00FF;

    //set initial duty cycle to 0% (use OC3RS to set duty cycle in future code)
    OC3RS = 0x0000;
    OC3R = 0x0000;
    
    OC4RS = 0x0000;
    OC4R = 0x0000;

    //configure OC3 and OC4 to PWM mode -- no fault detection -- sleep on CPU
    //sleep -- use timer 2
    OC3CON = 0x2006;
    OC4CON = 0x2006;

    //enable Timer 2 to start PWM
    //set prescalar to 256
    T2CON |= 0x8030;

    return;
}


void initTimer() {
    return;
}




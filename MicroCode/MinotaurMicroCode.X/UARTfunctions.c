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


//Set up the UART module to communicate with ATOM board
//Use 19200 baud rate
void initUART() {
    //set baud rate to 19200
    U2BRG = 12;

    //Enable the UART module -- 8-bit mode even parity
    U2MODE = 0x8002;      //1000000000000010

    //Status register
    //Interrupt when transmit buffer becomes empty
    //Interrupt when any character is received
    U2STA = 0x8400;  //1000010000000000
    
    return;
}


char *intToString(int num, char *end) {
    int temp, base;
    int i = 0;
    char retString[10];
    
    *end = '\0';

    while (num != 0) {
        *--end = '0' + (num%10);
        num /= 10;
    }

    return end;

}

//place the sting sent to function into the TX_DATA_BUFFER to send data
void printString(char *string) {
    int i = TX_DATA_BUFFER.place + 1;

    while(string[i] != '\0') {
        TX_DATA_BUFFER.DATA[i];
    }
}
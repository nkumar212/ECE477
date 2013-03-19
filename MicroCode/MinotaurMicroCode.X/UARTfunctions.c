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


void prInt(int num) {
    char temp_string[64];
    int i;

    temp_string[63] = '\0';

    i = 63;
    while (num != 0) {
        temp_string[--i] = '0' + (num%10);
        num /= 10;
    }

    printString(temp_string+i);
    return;

}

//place the sting sent to function into the TX_DATA_BUFFER to send data
void printString(char *string) {
    int j = 0;
    
    while(string[j] != '\0') {
        while(BUFF_status(&TX_DATA_BUFFER) == BUFF_FULL); //wait if buffer is full
        BUFF_push(&TX_DATA_BUFFER, string[j]);
        
        j++;
    }
}



//FUNCTIONS TO IMPLEMENT CIRCULAR BUFFER
int BUFF_push(BUFFER* buff, char c) {
  if((buff->tail + 1) % MAX_BUFFSIZE == buff->head) {
    return BUFF_FULL;
  } else {
    buff->data[buff->tail] = c;
    buff->tail = (buff->tail + 1) % MAX_BUFFSIZE;
  }
  return BUFF_NORMAL;
}

char BUFF_pop(BUFFER* buff) {
  char c = -1;
  if(buff->head == buff->tail) {
    return BUFF_EMPTY;
  } else {
    c = buff->data[buff->head];
    buff->head = (buff->head + 1) % MAX_BUFFSIZE;
  }
  return c;
}

int BUFF_status(BUFFER* buff) {
  if(buff->head == buff->tail) {
    return BUFF_EMPTY;
  } else if ((buff->tail + 1) % MAX_BUFFSIZE == buff->head) {
    return BUFF_FULL;
  } else {
    return BUFF_NORMAL;
  }
}

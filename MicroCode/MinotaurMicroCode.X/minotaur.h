/* 
 * File:   minotaur.h
 * Author: team16
 *
 * Created on February 12, 2013, 5:02 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_BUFFSIZE 50

#define BUFF_FULL 1
#define BUFF_EMPTY -1
#define BUFF_NORMAL 0

//Buffer used for transmitting and recieving data
typedef struct _BUFFER {
  int head;
  int tail;
  char data[MAX_BUFFSIZE];
} BUFFER;

int BUFF_push(BUFFER*, char);
char BUFF_pop(BUFFER*);
int BUFF_status(BUFFER*);


//structure for recieving control data
typedef struct _controlData {
    char command;
    char value;
} controlData;


extern BUFFER TX_DATA_BUFFER;
extern BUFFER RX_DATA_BUFFER;

//declare ADC related functions
long getIrSensorRange(char);
void initADC();

//PWM related functions
void initPWM();


//Timer related functions
void initTimer();

//Input capture
void initInputCapture();

//uart functions
void initUART();
void prInt(int);
void printString(char *);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


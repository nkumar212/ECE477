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

//UART DATA BUFFERS
extern BUFFER TX_DATA_BUFFER;
extern BUFFER RX_DATA_BUFFER;

//I2C DATA BUFFERS
extern BUFFER I2C_RX_BUFFER;
extern BUFFER I2C_TX_BUFFER;


//---------------------------------------------
//             FUNCTIONS
//---------------------------------------------

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
void printInt(int);
void printString(char *);

//I2C functions
void i2c_init(void);
int i2c_start(void);
int i2c_restart(void);
void reset_i2c_bus(void);
int send_byte_i2c(char data);
char i2c_read_set(void);
char read_i2c_byte_ack(void);
char read_i2c_byte_nack(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


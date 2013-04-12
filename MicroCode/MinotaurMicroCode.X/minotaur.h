/* 
 * File:   minotaur.h
 * Author: team16
 *
 * Created on February 12, 2013, 5:02 PM
 */

#ifndef MIN_H
#define	MIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_BUFFSIZE 100

#define BUFF_FULL 1
#define BUFF_EMPTY -1
#define BUFF_NORMAL 0

#define CMD_MOTORS 0x01
#define CMD_GET_SENSOR_DATA 0xB0
#define CMD_SENSOR 0xB1
//#define CMD_SENSOR1 0xB1
#define CMD_SENSOR2 0xB2
#define CMD_SENSOR3 0xB3
#define CMD_SENSOR4 0xB4
#define CMD_SENSOR5 0xB5
#define CMD_RIGHT_ENCODER 0xB6
#define CMD_LEFT_ENCODER 0xB7
#define CMD_BATTERY 0x02


#define SEN_MIN 400    //the minimum distance that the downward IR sensors have to sense
#define SEN_MAX 1000    //the distance at which the robot tries to avoid an object

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
    unsigned char bytesRecieved;  //the number of bytes that have been recieved in the
                         //current packet (should be a total of 5
    
    unsigned char sequence;
    unsigned char command;
    unsigned char data1;
    unsigned char data2;
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

#endif	/* MIN_H */


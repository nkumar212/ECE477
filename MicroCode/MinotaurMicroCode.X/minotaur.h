/* 
 * File:   adc.h
 * Author: team16
 *
 * Created on February 12, 2013, 5:02 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

//structure for recieving control data
typedef struct _controlData {
    char command;
    char value;
} controlData;



//declare ADC related functions
long getIrSensorRange(char);
void initADC();

//PWM related functions
void initPWM();


//Timer related functions
void initTimer();

//uart functions
void initUART();

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "warnmail.h"

void warn(char* toAddr);
void warn(char* toAddr, char* filename);

void warn(char* toAddr){

	// First, get the local time and date of the incident
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	// Initialize and populate a buffer containing the message to be sent
	char msgBuffer[110];
	sprintf(msgBuffer, "An intruder was detected by the minotaur at the following local time and date: %s",asctime(timeinfo));

	// Initialize and populate a buffer containing the sendEmail command and its flags
	char cmdBuffer[400];
	sprintf(cmdBuffer,"sendEmail -f 477Minotaur@gmail.com -t %s -u \"Minotaur Security\" -m \"%s\" -s smtp.gmail.com:587 -o tls=yes -xu 477Minotaur@gmail.com -xp ZAQ\!XSW@ -q",toAddr,msgBuffer);

	// Execute the command
	system(cmdBuffer);
}

void warn(char* toAddr, char* filename){

	// First, get the local time and date of the incident
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);

	// Initialize and populate a buffer containing the message to be sent
	char msgBuffer[160];
	sprintf(msgBuffer, "An intruder was detected by the minotaur at the following local time and date: %s. See attached file for picture.",asctime(timeinfo));

	// Initialize and populate a buffer containing the sendEmail command and its flags
	char cmdBuffer[500];
	sprintf(cmdBuffer,"sendEmail -f 477Minotaur@gmail.com -t %s -u \"Minotaur Security\" -m \"%s\" -s smtp.gmail.com:587 -o tls=yes -xu 477Minotaur@gmail.com -xp ZAQ\!XSW@ -q -a %s",toAddr,msgBuffer,filename);

	// Execute the command
	system(cmdBuffer);
}

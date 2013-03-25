#ifndef MAIN_SYNCHRONOUS_H
#define MAIN_SYNCHRONOUS_H
#include <pthread>
#include <iostream>

#include "commandqueue.h"

int mainSynchronous(void* vCmdQueue)
{
	CommandQueue* cmd_q = vCmdQueue;
	while(!cmd_q.quit())
	{
		//Synchronous loop
	}
}
#endif

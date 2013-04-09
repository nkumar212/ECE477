#include <iostream>
#include <pthread.h>
#include <cassert>
#include <cstdio>

#include "CommandQueue.h"
#include "main_command_queue.h"
#include "main_synchronous.h"
#include "main_cnc_wait.h"

int main(int argc, char* argv[])
{
//	setvbuf(stdout, NULL, _IONBF, 0);
	pthread_t t_timer_loop;
	pthread_t t_command_queue;
	int rc;

	IDS* ids = IDS::getSingleton();
	CommandQueue* cmdq = CommandQueue::getSingleton();
	Kinect* kinect = ids->getKinect();

/*	ids->cnc_connect("localhost", 50000);

	rc = pthread_create(&t_command_queue, NULL, mainCommandQueue, (void*)ids);
	assert(!rc);*/

/*	rc = pthread_create(&t_timer_loop, NULL, mainSynchronous, (void*)ids);
	assert(!rc);*/

/*	rc = pthread_create(&t_timer_loop, NULL, mainCncWait, (void*)ids);
	assert(!rc);*/

	while(1)
		kinect->process_events();

	rc = pthread_join(t_command_queue, NULL);
	assert(!rc);

	rc = pthread_join(t_timer_loop, NULL);
	assert(!rc);

	return 0;
}

#include <iostream>
#include <pthread.h>
#include <cassert>
#include <cstdio>

#include "CommandQueue.h"
#include "main_command_queue.h"
#include "main_synchronous.h"
#include "main_cnc_wait.h"
#include "main_minos_wait.h"

int main(int argc, char* argv[])
{
//	setvbuf(stdout, NULL, _IONBF, 0);
	pthread_t t_timer_loop;
	pthread_t t_command_queue;
	pthread_t t_minos_loop;
	pthread_t t_cnc_loop;
	int rc;

	IDS* ids = IDS::getSingleton();
	CommandQueue* cmdq = CommandQueue::getSingleton();
	Kinect* kinect = ids->getKinect();

	ids->cnc_connect(argv[1], 50000);
	ids->minos_connect();

	rc = pthread_create(&t_command_queue, NULL, mainCommandQueue, (void*)ids);
	assert(!rc);

	rc = pthread_create(&t_timer_loop, NULL, mainSynchronous, (void*)ids);
	assert(!rc);

	rc = pthread_create(&t_cnc_loop, NULL, mainCncWait, (void*)ids);
	assert(!rc);

	rc = pthread_create(&t_minos_loop, NULL, mainMinosWait, (void*)ids);
	assert(!rc);

	while(1)
		kinect->process_events();

	rc = pthread_join(t_command_queue, NULL);
	assert(!rc);

	rc = pthread_join(t_timer_loop, NULL);
	assert(!rc);

	return 0;
}

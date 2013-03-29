#include <iostream>
#include <pthread.h>
#include <cassert>

#include "CommandQueue.h"
#include "main_command_queue.h"
//#include "main_synchronous.h"

int main(int argc, char* argv[])
{
	pthread_t t_timer_loop;
	pthread_t t_command_queue;
	int rc;

	IDS* ids = IDS::getSingleton();

	ids->cnc_connect("localhost", 50000);

	rc = pthread_create(&t_command_queue, NULL, mainCommandQueue, (void*)ids);
	assert(!rc);

/*	rc = pthread_create(&t_timer_loop, NULL, mainSynchronous, &cmd_q);
	assert(!rc);*/

	rc = pthread_join(t_command_queue, NULL);
	assert(!rc);

/*	rc = pthread_join(t_timer_loop, NULL);
	assert(!rc);*/

	return 0;
}
#include <iostream>
#include <pthread.h>
#include <cassert>

#include "commandqueue.h"
#include "main_command_queue.h"
#include "main_synchronous.h"

int main(int argc, char* argv[])
{
	pthread_t t_timer_loop;
	pthread_t t_command_queue;

	CommandQueue cmd_q;

	int rc;

	rc = pthread_create(&t_command_queue, NULL, mainCommandQueue, &cmd_q);
	assert(!rc);

	rc = pthread_create(&t_timer_loop, NULL, mainSynchronous, &cmd_q);
	assert(!rc);

	rc = pthread_join(t_command_queue, NULL);
	assert(!rc);

	rc = pthread_join(t_timer_loop, NULL);
	assert(!rc);

	return 0;
}

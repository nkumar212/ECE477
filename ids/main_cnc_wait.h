#ifndef MAIN_CNCWAIT_H
#define MAIN_CNCWAIT_H
#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <sys/socket.h>
#include <errno.h>

#include "CommandQueue.h"
#include "commands/commands.h"
#include "ids.h"

#define CNCWAIT_LOOP_TIME (1000.0/15.00)

void* mainCncWait(void* vids)
{ 
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(1, &cpuset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

	long now_ms, loop_ms;
	timespec t1;
	IDS* ids = static_cast<IDS*>(vids);
	Kinect* kinect = ids->getKinect();
	uint8_t* vbuff;
	int datalen;

	clock_gettime(CLOCK_MONOTONIC, &t1);
	loop_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000);

	ComDumpDist cmdDumpDist;
	CommandQueue* cmdq = CommandQueue::getSingleton();

	while(!ids->quit())
	{
		loop_ms += LOOP_TIME;

		datalen = ids->cnc_checkmsg();
		if(errno != EWOULDBLOCK)
		{
			fprintf(stderr,"%s",ids->cnc_getbuffer());
			cmdq->push(&cmdDumpDist);
		}

		clock_gettime(CLOCK_MONOTONIC, &t1);
		now_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000);

		while(loop_ms > now_ms)
		{
			usleep(20);
			clock_gettime(CLOCK_MONOTONIC, &t1);
			now_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000);
		}
	}

	return NULL;
}
#endif

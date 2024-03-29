#ifndef MAIN_SYNCHRONOUS_H
#define MAIN_SYNCHRONOUS_H
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

#define LOOP_TIME (1000000.0/23.98)

void* mainSynchronous(void* vids)
{ 
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(1, &cpuset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

	long now_us, loop_ms;
	timespec t1;
	IDS* ids = static_cast<IDS*>(vids);
	Kinect* kinect = ids->getKinect();
	uint8_t* vbuff;
	int datalen;

	clock_gettime(CLOCK_MONOTONIC, &t1);
	loop_ms = (t1.tv_sec * 1000000 + t1.tv_nsec/1000);

	CommandQueue* cmdq = CommandQueue::getSingleton();

	while(!ids->quit())
	{
		loop_ms += LOOP_TIME;

		vbuff = kinect->nextVideoFrameYUV();
		fwrite(vbuff,320*6/4,240,stdout);

		clock_gettime(CLOCK_MONOTONIC, &t1);
		now_us = (t1.tv_sec * 1000000 + t1.tv_nsec/1000);

		while(loop_ms > now_us)
		{
			usleep(20);
			clock_gettime(CLOCK_MONOTONIC, &t1);
			now_us = (t1.tv_sec * 1000000 + t1.tv_nsec/1000);
		}
	}

	return NULL;
}
#endif

#ifndef MAIN_MINOSWAIT_H
#define MAIN_MINOSWAIT_H
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
#include "minotaur.h"

#define MINOSWAIT_LOOP_TIME (1000.0/5.00)

void* mainMinosWait(void* vids)
{ 
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(1, &cpuset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

	long now_ms, loop_ms;
	timespec t1;
	IDS* ids = static_cast<IDS*>(vids);
	Kinect* kinect = ids->getKinect();
	Minotaur* minotaur = ids->getMinotaur();
	uint8_t* vbuff;
	int datalen;

	clock_gettime(CLOCK_MONOTONIC, &t1);
	loop_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000);

	CommandQueue* cmdq = CommandQueue::getSingleton();

	minotaur->sendpacket(0x01,0x0000);

	while(!ids->quit())
	{
		loop_ms += MINOSWAIT_LOOP_TIME;

		while(minotaur->recv())
			;
		
		minotaur->sendpacket(0xB0,0x0000);

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

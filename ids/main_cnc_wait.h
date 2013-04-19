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



struct CNCCommand
{
	uint8_t command;

	union
	{
		uint16_t udata16;
		uint8_t udata8[2];
	};
};

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

	ComDumpVideo cmdDumpVideo;
	CommandQueue* cmd_q = CommandQueue::getSingleton();
	CNCCommand cncCmd;


	while(!ids->quit())
	{
		loop_ms += CNCWAIT_LOOP_TIME;

		datalen = ids->cnc_checkmsg();
		if(errno != EWOULDBLOCK)
		{
			if(datalen != 3)
			{
				/*while(datalen > 0)
					fprintf(stderr,"%02X ", ids->cnc_getbuffer()[--datalen]);
				fprintf(stderr,"\n");*/

				throw std::runtime_error("Invalid Command packet length from CNC Server.\n");
			}

			cncCmd.command = ids->cnc_getbuffer()[0];
			cncCmd.udata8[0] = ids->cnc_getbuffer()[1];
			cncCmd.udata8[1] = ids->cnc_getbuffer()[2];

			//fprintf(stderr,"0x%02X 0x%04X\n",cncCmd.command,cncCmd.udata16);

			switch(cncCmd.command)
			{
				case 0x01: //Motors Move
					ids->minos_sendpacket(cncCmd.command,cncCmd.udata16);
					break;
				case 0x10: //Take picture
					cmd_q->push(&cmdDumpVideo);
					std::cerr << "Caught dump command" << std::endl;
					break;
				default:
					throw std::runtime_error("Invalid Command pakcet cmdNumber from CNC Server.\n");
			}
		}

		clock_gettime(CLOCK_MONOTONIC, &t1);
		now_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000);

//		fprintf(stderr,"%ld %ld\n", loop_ms, now_ms);

		while(loop_ms > now_ms)
		{
			usleep(200);
			clock_gettime(CLOCK_MONOTONIC, &t1);
			now_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000);
		}
	}

	return NULL;
}
#endif

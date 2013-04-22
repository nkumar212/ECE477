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
	Minotaur* minotaur = ids->getMinotaur();
	uint8_t* vbuff;
	int datalen;

	clock_gettime(CLOCK_MONOTONIC, &t1);
	loop_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000);

	ComDumpVideo* cmdDumpVideo = new ComDumpVideo();
	ComWallFrame cmdFrameSourceWallFrame;
	CommandQueue* cmd_q = CommandQueue::getSingleton();
	Minotaur::MinotaurStatePacked packedMinoState;
	CNCCommand cncCmd;

	ComFrameProxy comFrameProxy;
	cmd_q->add_periodic(&comFrameProxy, 100);
	comFrameProxy.registerFrameSource("PosFrameXYZ", new ComPosFrame(
					ComPosFrame::X | ComPosFrame::Y | ComPosFrame::Z
				));
	comFrameProxy.registerFrameSource("PosFrameX", new ComPosFrame(
					ComPosFrame::X
				));
	comFrameProxy.registerFrameSource("PosFrameY", new ComPosFrame(
					ComPosFrame::Y
				));
	comFrameProxy.registerFrameSource("PosFrameZ", new ComPosFrame(
					ComPosFrame::Z
				));
	comFrameProxy.registerFrameSource("MapFrame", new ComMapFrame());
	comFrameProxy.registerFrameSource("WallFrame", new ComWallFrame());
	comFrameProxy.registerFrameSource("Live", NULL);

	comFrameProxy.chooseSource(ids, "Live");


	while(!ids->quit())
	{
		loop_ms += CNCWAIT_LOOP_TIME;

		datalen = ids->cnc_checkmsg();
		if(errno != EWOULDBLOCK && datalen > 0)
		{
			if(datalen != 3)
			{
				fprintf(stderr,"From CNC: ");
				while(datalen > 0)
					fprintf(stderr,"%02X ", ids->cnc_getbuffer()[--datalen]);
				fprintf(stderr,"\n");

				throw std::runtime_error("Invalid Command packet length from CNC Server.\n");
			}

			cncCmd.command = ids->cnc_getbuffer()[0];
			cncCmd.udata8[0] = ids->cnc_getbuffer()[1];
			cncCmd.udata8[1] = ids->cnc_getbuffer()[2];

			if(cncCmd.command != 0x30)
				fprintf(stderr,"From Cnc: 0x%02X 0x%04X\n",cncCmd.command,cncCmd.udata16);

			switch(cncCmd.command)
			{
				case 0x01: //Motors Move
					ids->getMinotaur()->sendpacket(cncCmd.command,cncCmd.udata16);
					break;
				case 0x10: //Take picture
					cmd_q->push(cmdDumpVideo);
					break;
				case 0x20:
					switch(cncCmd.udata16)
					{
						case 0x01:
							comFrameProxy.chooseSource(ids,"PosFrameX");
							break;
						case 0x02:
							comFrameProxy.chooseSource(ids,"PosFrameY");
							break;
						case 0x04:
							comFrameProxy.chooseSource(ids,"PosFrameZ");
							break;
						case 0x07:
							comFrameProxy.chooseSource(ids,"PosFrameXYZ");
							break;
					}

					std::cerr << "Caught source change to PosFrame(" << cncCmd.udata16 << ")" << std::endl;
					break;
				case 0x21:
					comFrameProxy.chooseSource(ids,"WallFrame");
					std::cerr << "Caught source change to WallFrame" << std::endl;
					break;
				case 0x22:
					comFrameProxy.chooseSource(ids,"MapFrame");
					std::cerr << "Caught source change to MapFrame" << std::endl;
					break;
				case 0x23:
					comFrameProxy.chooseSource(ids,"Live");
					std::cerr << "Caught source change to Live" << std::endl;
					break;
				case 0x30:
					packedMinoState = Minotaur::MinotaurStatePacked(minotaur->getState());
					ids->cnc_rawmsg(&packedMinoState, sizeof(packedMinoState));
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

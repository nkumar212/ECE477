#ifndef MAIN_COMMAND_QUEUE_H
#define MAIN_COMMAND_QUEUE_H
#include <iostream>
#include <ctime>
#include <stdexcept>

#include "CommandQueue.h"
#include "commands/commands.h"
#include "ids.h"

void* mainCommandQueue(void* vIDS)
{
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

	IDS* ids = static_cast<IDS*>(vIDS);
	CommandQueue* cmd_q = ids->getCmdQueue();
	Command* cmd = NULL;

	cmd_q->add_periodic(new ComKeepalive(), 100);
	cmd_q->add_periodic(new ComSwapDepth(), 99);
	//cmd_q->add_periodic(new ComPlaneDist(), 100);


	ComWallFrame* cmdWallFrame = new ComWallFrame();
	cmd_q->add_periodic(cmdWallFrame, 50);
	ids->getKinect()->setVideoSource((uint8_t*)cmdWallFrame->frame);

/*	ComPosFrame* cmdPosFrame = new ComPosFrame();
	cmd_q->add_periodic(cmdPosFrame, 50);
	ids->getKinect()->setVideoSource((uint8_t*)cmdPosFrame->frame);*/

	ids->swapDepth();


	long start_ms, end_ms;
	timespec t1;

	while(!ids->quit())
	{
		if(cmd_q->size() > 100) throw std::runtime_error("Command Queue overflow detected.");

		if(cmd_q->size() > 0)
		{
			cmd = cmd_q->front();
			cmd_q->pop();

			ids->lock_output();

			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
			start_ms = (t1.tv_sec * 1000000 + t1.tv_nsec/1000);

			cmd->action(ids);

			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
			end_ms = (t1.tv_sec * 1000000 + t1.tv_nsec/1000);

/*			if(end_ms - start_ms > 1000)
				std::cerr << "Command '" << cmd->getName() << "' took " << (end_ms - start_ms) << "us" << std::endl;*/

			ids->unlock_output();
		}else{
			usleep(500);
		}

		cmd_q->gen_periodic();
	}

	while(!cmd_q->empty())
	{
		cmd = cmd_q->front();
		cmd_q->pop();
		cmd->action(ids);
	}

	return NULL;
}
#endif

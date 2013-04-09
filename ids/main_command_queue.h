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

	ComSlopeFrame* cmdSlopeFrame = new ComSlopeFrame();

	cmd_q->add_periodic(new ComKeepalive(), 10000);
	cmd_q->add_periodic(new ComSwapDepth(), 99);
	//cmd_q->add_periodic(new ComPlaneDist(), 100);
	//cmd_q->add_periodic(cmdSlopeFrame, 1000);
	//ids->getKinect()->setVideoSource((uint8_t*)cmdSlopeFrame->frame);

	ids->swapDepth();

	while(!ids->quit())
	{
		if(cmd_q->size() > 100) throw std::runtime_error("Command Queue overflow detected.");

		if(cmd_q->size() > 0)
		{
			cmd = cmd_q->front();
			cmd_q->pop();
			ids->lock_output();
			cmd->action(ids);
			std::cerr << cmd->getName() << std::endl;
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

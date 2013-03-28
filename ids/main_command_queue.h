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
	IDS* ids = static_cast<IDS*>(vIDS);
	CommandQueue* cmd_q = ids->getCmdQueue();
	Command* cmd = NULL;

	cmd_q->add_periodic(new ComKeepalive(), 2000);

	while(!ids->quit())
	{
		if(cmd_q->size() > 100) throw std::runtime_error("Command Queue overflow detected.");

		if(cmd_q->size() > 0)
		{
			cmd = cmd_q->front();
			cmd_q->pop();
			cmd->action(ids);
		}

		cmd_q->gen_periodic();
	}

	while(!cmd_q->empty())
	{
		cmd = cmd_q->front();
		cmd_q->pop();
		cmd->action(ids);
	}
}
#endif

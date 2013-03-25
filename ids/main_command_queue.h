#ifndef MAIN_COMMAND_QUEUE_H
#define MAIN_COMMAND_QUEUE_H
#include <pthread>
#include <iostream>
#include <ctime>
#include <stdexcept>

#include "commandqueue.h"

class Command;

static inline void gen_periodic(CommandQueue* cmd_q, Periodic* per_cmds, int pnum)
{
	static timespec t1;
	static unsigned long now_ms;
	static int p;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
	now_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000000);

	for(p = 0; p < pnum; p++)
	{
		if(now_ms - per_cmds[p].next >= 0)
		{
			cmd_q->push_back(per_cmds[p].cmd);
			if(per_cmds[p].next == 0) per_cmds[p].next = now_ms;
			per_cmds[p].next += per_cmds[p].period;
		}
	}
}

int mainCommandQueue(void* vCmdQueue)
{
	CommandQueue* cmd_q = vCmdQueue;
	Command* cmd = NULL;

	Periodic per_cmds[] = {
		{1000, 0, 0, new CmdNetKeepAlive()}
	};

	int pnum = (sizeof per_cmds) / (sizeof Periodic);

	while(!cmd_q->quit())
	{
		if(cmd_q->size() > 100) throw std::runtime_error("Command Queue overflow detected.")

		if(cmd_q->size() > 0)
		{
			cmd = cmd_q->pop_front();
			handle_cmd(cmd);
		}

		gen_periodic(cmd_q, per_cmds, pnum);
	}

	while(!cmd_q->empty())
	{
		cmd = cmd_q->pop();
		handle_cmd(cmd);
	}
}
#endif

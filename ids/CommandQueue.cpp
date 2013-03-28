#include "CommandQueue.h"

CommandQueue* CommandQueue::singleton = NULL;

CommandQueue::CommandQueue()
{
	if(singleton)
		throw std::runtime_error("Attempted to initialize two copies of singleton class: CommandQueue");
	singleton = this;
}


CommandQueue* CommandQueue::getSingleton()
{
	if(singleton) return singleton;
	else return new CommandQueue();
}

Command* CommandQueue::front()
{
	return q.front();
}

Command* CommandQueue::back()
{
	return q.back();
}

size_t CommandQueue::size()
{
	return q.size();
}

bool CommandQueue::empty()
{
	return q.empty();
}

void CommandQueue::pop()
{
	q.pop();
}

void CommandQueue::push(Command* c)
{
	q.push(c);
}

void CommandQueue::gen_periodic()
{
	timespec t1;
	long now_ms;
	std::vector<Periodic>::iterator it;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
	now_ms = (t1.tv_sec * 1000 + t1.tv_nsec/1000000);

	for(it = per_cmds.begin(); it != per_cmds.end(); it++)
	{
		if(now_ms - it->next >= 0)
		{
			printf("%s %ld/%ld\n", it->cmd->getName().c_str(), now_ms, it->period);
			push(it->cmd);
			if(it->next == 0) it->next = now_ms;
			it->next += it->period;
			++it->count;
		}
	}
}

void CommandQueue::add_periodic(Command* c, long per)
{
	Periodic p;
	p.period = per;
	p.next = 0;
	p.count = 0;
	p.cmd = c;

	per_cmds.push_back(p);
}

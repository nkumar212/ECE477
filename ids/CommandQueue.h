#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <queue>
#include <pthread.h>
#include <ctime>
#include <stdexcept>
#include <ctime>
#include <vector>

#include "Command.h"

class CommandQueue
{
	protected: //Types
		typedef struct {
			long period;
			long next;
			long count;
			Command* cmd;
		} Periodic;

	protected: //Static Variables

		//Implements singleton pattern
		static class CommandQueue* singleton;

	protected: //Properties
		std::queue<Command*> q;
		std::vector<Periodic> per_cmds;

	protected: //Constructor (Singleton)
		CommandQueue();

	public: //Static Members
		static CommandQueue* getSingleton();

	public: //Instance Members
		void gen_periodic();
		void add_periodic(Command* c, long per);

		Command* front();
		Command* back();
		void pop();
		void push(Command*);
		size_t size();
		bool empty();
};

#endif

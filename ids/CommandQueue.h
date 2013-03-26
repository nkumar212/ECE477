#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <queue>
#include <pthread>
#include <ctime>
#include <stdexcept>

#include "command.h"

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

		//Configuration for periodic commands to be added to the queue
		static Periodic per_cmds[];
		static int per_cmd_num;

	protected: //Properties
		std::queue<Command*> q;

	protected: //Constructor (Singleton)
		CommandQueue()
		{
			if(singleton)
				throw sd::runtime_error("Attempted to initialize two copies of singleton class: CommandQueue");
			singleton = this;
		}

	public: //Static Members
		static CommandQueue* getSingleton()
		{
			if(singleton) return singleton;
			else return new CommandQueue();
		}

	public: //Instance Members
		Command* front();
		Command* back();
		void pop();
		void push(Command*);
		size_t size();
		bool empty();
};

#endif

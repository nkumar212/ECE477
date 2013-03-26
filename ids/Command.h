#ifndef COMMAND_H
#define COMMAND_H

#include <stdexcept>

class IDS;

class Command
{
	protected:
		std::string name;
	protected:
		Command(std::string name);
	public:
		virtual int action(IDS* main) = 0;
};

#endif

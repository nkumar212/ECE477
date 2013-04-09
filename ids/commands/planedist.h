#ifndef PLANEDIST_H
#define PLANEDIST_H

#include "../Command.h"
#include "../ids.h"

class ComPlaneDist : public Command
{
	public:
		ComPlaneDist();
		virtual int action(IDS* main);
};

#endif

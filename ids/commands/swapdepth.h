#ifndef SWAPDEPTH_H
#define SWAPDEPTH_H

#include "../Command.h"
#include "../ids.h"

class ComSwapDepth : public Command
{
	public:
		ComSwapDepth();
		virtual int action(IDS* main);
};

#endif

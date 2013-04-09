#ifndef FREENECT_SYNC_H
#define FREENECT_SYNC_H

#include "../Command.h"
#include "../ids.h"

class ComFreenectSync : public Command
{
	public:
		ComFreenectSync();
		virtual int action(IDS* main);
};

#endif

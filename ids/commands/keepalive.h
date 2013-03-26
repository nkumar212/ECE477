#ifndef KEEPALIVE_H
#define KEEPALIVE_H

#include "../Command.h"
#include "../ids.h"

class ComKeepalive : public Command
{
	public:
		ComKeepalive();
		virtual int action(IDS* main);
};

#endif

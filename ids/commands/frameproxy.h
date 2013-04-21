#ifndef FRAMEPROXY_H
#define FRAMEPROXY_H

#include "frame.h"
#include "../Command.h"
#include <iostream>
#include <map>

class ComFrameProxy : public Command
{
	protected:
		std::map<std::string, ComFrame*> registry;
		ComFrame* source;
		IDS* target;
	public:
		ComFrameProxy();
		virtual int action(IDS* main);
		void registerFrameSource(std::string, ComFrame*);
		void chooseSource(IDS* main, std::string src);
};

#endif

#ifndef FINDLINE_H
#define FINDLINE_H

#include "../Command.h"
#include "../ids.h"

class ComFindLine : public Command
{
	public:
		ComFindLine();
		virtual int action(IDS* main);
		Kinect::video_buffer* frame;
};

#endif

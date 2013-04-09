#ifndef DISTFRAME_H
#define DISTFRAME_H

#include "../Command.h"
#include "../ids.h"

class ComDistFrame : public Command
{
	public:
		ComDistFrame();
		virtual int action(IDS* main);
		Kinect::video_buffer* frame;
};

#endif

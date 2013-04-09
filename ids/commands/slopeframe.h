#ifndef SLOPEFRAME_H
#define SLOPEFRAME_H

#include "../Command.h"
#include "../ids.h"
#include <cmath>
#include <algorithm>

class ComSlopeFrame : public Command
{
	public:
		ComSlopeFrame();
		virtual int action(IDS* main);
		Kinect::video_buffer* frame;
};

#endif

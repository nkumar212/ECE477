#ifndef FRAME_H
#define FRAME_H

#include "../Command.h"
#include "../kinect.h"
#include <iostream>

class IDS;

class ComFrame : public Command
{
	protected:
		Kinect::video_buffer frame;
	public:
		ComFrame(std::string);
		virtual int action(IDS* main) = 0;
		void setVideoSource(IDS* main);
};

#include "../ids.h"

#endif

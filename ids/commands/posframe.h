#ifndef POSFRAME_H
#define POSFRAME_H

#include "../Command.h"
#include "../ids.h"
#include <cmath>
#include <algorithm>

class ComPosFrame : public Command
{
	protected:
		struct Point
		{
			float x,y,z;
		};
		bool valid_points[8][8];
	public:
		ComPosFrame();
		virtual int action(IDS* main);
		Kinect::video_buffer frame;
};

#endif

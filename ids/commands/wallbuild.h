#ifndef WALLFRAME_H
#define WALLFRAME_H

#include "../Command.h"
#include "../ids.h"
#include <cmath>
#include <algorithm>

class ComWallFrame : public Command
{
	protected:
		struct Point
		{
			float x,y,z;
		};
		bool valid_points[8][8];
	public:
		ComWallFrame();
		virtual int action(IDS* main);
		Kinect::video_buffer frame;
};

#endif

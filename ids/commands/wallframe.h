#ifndef WALLFRAME_H
#define WALLFRAME_H

#include "frame.h"
#include <cmath>
#include <algorithm>

class ComWallFrame : public ComFrame
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
};

#endif

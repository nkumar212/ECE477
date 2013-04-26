#ifndef POSFRAME_H
#define POSFRAME_H

#include <cmath>
#include <algorithm>

#include "frame.h"

class ComPosFrame : public ComFrame
{
	public:
		enum { X=1, Y=2, Z=4 };
	protected:
		struct Point
		{
			float x,y,z;
		};
		bool valid_points[8][8];
		int xyzflags;
		float decode_kinect_dist[KINECT_CALIB_DOFF+1];
	public:
		ComPosFrame(int xyzflags = 7);
		virtual int action(IDS* main);
};

#endif

#ifndef WALLFRAME_H
#define WALLFRAME_H

#include "frame.h"
#include "../wall.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <utility>

#include <fftw3.h>

#define WALL_AVG_SIZE 4

class ComWallFrame : public ComFrame
{
	protected:
		struct Point
		{
			float x,y,z;
		};
		bool valid_points[8][8];
		float decode_kinect_dist[KINECT_CALIB_DOFF+1];
	public:
		ComWallFrame();
		virtual int action(IDS* main);
};

#endif

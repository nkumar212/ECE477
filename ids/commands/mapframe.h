#ifndef MAPFRAME_H
#define MAPFRAME_H

#include "frame.h"
#include "../map.h"
#include <cmath>
#include <algorithm>

class ComMapFrame : public ComFrame
{
	protected:
		struct Point
		{
			float x,y,z;
		};
		bool valid_points[8][8];
		float decode_kinect_dist[1029];
	public:
		ComMapFrame();
		virtual int action(IDS* main);
};

#endif

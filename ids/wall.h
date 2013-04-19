#ifndef WALL_H
#define WALL_H

#include <cmath>

#define ORIENT_EQUAL_THRESH 0.01
#define INTERCEPT_EQUAL_THRESH 12.0

inline bool diff_angle(float a, float b)
{
	float d = a - b;
	d += (d>180) ? -360 : (d<-180) ? 360 : 0;
	return d;
}

struct Wall
{
	float orient, yint;
	int point_count;

	Wall(float orient, float yint);

	inline bool operator==(const Wall& rhs) const
	{
		if(fabs(rhs.yint - this->yint) < INTERCEPT_EQUAL_THRESH)
			if(fabs(diff_angle(rhs.orient, this->orient)) < ORIENT_EQUAL_THRESH)
				return true;

		return false;
	}

	inline bool operator!=(const Wall& rhs) const {return !(*this == rhs);}
	inline bool operator< (const Wall& rhs) const
	{
		if(fabs(rhs.yint - this->yint) < INTERCEPT_EQUAL_THRESH)
			if(fabs(diff_angle(rhs.orient, this->orient)) < ORIENT_EQUAL_THRESH)
				return false;
			else
				return this->orient < rhs.orient;
		else
			return this->yint < rhs.yint;
	}
	
	inline bool operator> (const Wall& rhs) const {return rhs < *this;}
	inline bool operator<=(const Wall& rhs) const {return !(*this>rhs);}
	inline bool operator>=(const Wall& rhs) const {return !(*this<rhs);}
};

#endif

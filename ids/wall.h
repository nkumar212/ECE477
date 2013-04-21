#ifndef WALL_H
#define WALL_H

#include <cmath>
#include <stdint.h>

#define ORIENT_EQUAL_THRESH 0.2
#define INTERCEPT_EQUAL_THRESH 1200

#ifndef PI
#define PI 3.1415926535
#endif

inline float diff_angle(float a, float b)
{
	float d = a - b;
	d += (d>PI) ? -2*PI : (d<-PI) ? 2*PI : 0;
	return d;
}

struct Wall
{
	float orient, yint;

	Wall(float orient=0, float yint=0);

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
		if(fabs(diff_angle(rhs.orient, this->orient)) < ORIENT_EQUAL_THRESH)
			if(fabs(rhs.yint - this->yint) < INTERCEPT_EQUAL_THRESH)
				return false;
			else
				return this->yint < rhs.yint;
		else
			return this->orient < rhs.orient;
	}
	
	inline bool operator> (const Wall& rhs) const {return rhs < *this;}
	inline bool operator<=(const Wall& rhs) const {return !(*this>rhs);}
	inline bool operator>=(const Wall& rhs) const {return !(*this<rhs);}
};

#endif

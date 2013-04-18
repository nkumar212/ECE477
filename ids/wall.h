#ifndef WALL_H
#define WALL_H

#define ORIENT_EQUAL_THRESH 0.01
#define INTERCEPT_EQUAL_THRESH 12.0

inline bool diff_angle_less(float a, float b)
{
	float d = a - b
	d += (d>180) ? -360 : (d<-180) ? 360 : 0
	return d;
}

struct Wall
{
	float orient, yint;
	int point_count;

	inline bool operator==(const Wall& rhs) const
	{
		if(fabs(rhs.yint - this->yint) < INTERCEPT_EQUAL_THRESH)
			if(fabs(diff_angle(rhs.orient, this->orient)) < ORENT_EQUAL_THRESH)
				return true;

		return false;
	}

	inline bool operator!=(const Wall& rhs) const {return !operator==(*this,rhs);}
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
	
	inline bool operator> (const Wall& rhs) const {return  operator< (rhs,*this);}
	inline bool operator<=(const Wall& rhs) const {return !operator> (*this,rhs);}
	inline bool operator>=(const Wall& rhs) const {return !operator< (*this,rhs);}
};

#endif

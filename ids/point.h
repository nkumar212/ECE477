#ifndef POINT_H
#define POINT_H

#include <stdint.h>

struct Point
{
	uint32_t opencount, closedcount;

	Point(int x, int y);

	//Returns probability from 0 to 255 that a space is traversable
	inline uint8_t getProb()
	{
		return opencount * 255 / (opencount+closedcount);
	}

	inline void incOpen(){++opencount;}
	inline void incClosed(){++closedcount;}

	inline bool operator==(const Point& rhs) const
	{
		return (rhs.x == x) && (rhs.y == y);
	}

	inline bool operator!=(const Point& rhs) const {return !(*this == rhs);}
	inline bool operator< (const Point& rhs) const
	{
		return (y < rhs.y) ? (x < rhs.x) : false;
	}
	
	inline bool operator> (const Point& rhs) const {return rhs < *this;}
	inline bool operator<=(const Point& rhs) const {return !(*this>rhs);}
	inline bool operator>=(const Point& rhs) const {return !(*this<rhs);}
};

struct PointBlock
{
	int x,y;
	
};

#endif

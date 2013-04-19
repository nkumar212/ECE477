#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include <set>

class Wall;

struct Point
{
	uint32_t opencount, closedcount;
	std::set<Wall*> walls;

	Point();

	//Returns probability from 0 to 255 that a space is traversable
	inline uint8_t getProb()
	{
		return opencount * 255 / (opencount+closedcount);
	}

	inline void incOpen(){++opencount;}
	inline void incClosed(){++closedcount;}
};

#endif

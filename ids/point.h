#ifndef POINT_H
#define POINT_H

#include <stdint.h>
#include <set>

class Wall;

struct Point
{
	uint8_t opencount;
	uint32_t history[8];
	std::set<Wall*> walls;

	Point();

	//Returns probability from 0 to 255 that a space is traversable
	inline uint8_t getProb()
	{
		return opencount;
	}

	inline void shift(bool newbit){
		int i = 0;
		bool oldbit = false;

		if(newbit) ++opencount;

		for(i = 0; i < 8; i++)
		{
			oldbit = (0x80000000 & history[i]) ? true : false;
			history[i] = (history[i] << 1) + newbit;
			newbit = oldbit;
		}

		if(history[7] & 0x80000000) --opencount;
	}

	inline void incOpen(){
		shift(true);
	}

	inline void incClosed(){
		shift(false);
	}
};

#endif

#include "point.h"

Point::Point()
{
	opencount = 127;
	int i;

	for(i = 0; i < 8; i++)
		history[i] = 0xAAAAAAAA;
}


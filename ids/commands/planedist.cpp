#include "planedist.h"

ComPlaneDist::ComPlaneDist() : Command::Command("PlaneDist")
{
	
}

int ComPlaneDist::action(IDS* main)
{
	int x,y;
	float sum = 0;
	float dist;
	Kinect::depth_buffer* dframe = main->getDepth();
	uint16_t d0, d1;
	uint16_t d;
	int count = 0;
	float i;

	for(y = 230; y < 250; y++)
	{
		for(x = 310; x < 330; x++)
		{
			d0 = (*dframe)[y][x][0];
			d1 = (*dframe)[y][x][1];
			d = (d1 << 8) + d0;
			if(d != 2047)
			{
				i = 34800.0 / 2.54 / (1091.5 - d);
				sum += i;
				count++;
			}
		}
	}

	dist = (float)sum / count;

	fprintf(stderr,"Plane Distance: %f\"\n", dist);
}

#include "depthframe.h"

ComDepthFrame::ComDepthFrame() : ComFrame::ComFrame("DepthFrame")
{
}

int ComDepthFrame::action(IDS* main)
{
	int x,y,xo,yo;
	Kinect::depth_buffer* dframe = main->getDepth();
	Kinect* kinect = main->getKinect();

	uint8_t r,g,b;
	uint16_t d, d0, d1;


	for(y = 0; y < 480; y++)
	{
		for(x = 0; x < 640; x++)
		{
			d0 = (*dframe)[y][x][0];
			d1 = (*dframe)[y][x][1];
			d = d1;
			d = d << 8 | d0;

			frame[y][x][0] = d;
			frame[y][x][1] = d;
			frame[y][x][2] = d;
		}
	}

	return 0;
}


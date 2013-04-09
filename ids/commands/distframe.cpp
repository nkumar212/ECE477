#include "distframe.h"

ComDistFrame::ComDistFrame() : Command::Command("DistFrame")
{
	frame = (Kinect::video_buffer*)malloc(640*480*3);	
}

int ComDistFrame::action(IDS* main)
{
	int x,y;
	long sum;
	float dist;
	Kinect::depth_buffer* dframe = main->getDepth();
	uint8_t d1, d0;
	uint16_t d;

	for(y = 0; y < 480; y++)
	{
		for(x = 0; x < 640; x++)
		{
		       	d0 = (*dframe)[y][x][0];
		       	d1 = (*dframe)[y][x][1];
			d = d1;
			d = d << 8 | d0;
			if(d == 0x07FF)
			{
				(*frame)[y][x][0] = 0;
				(*frame)[y][x][1] = 0xFF;
				(*frame)[y][x][2] = 0;
			}else{
				(*frame)[y][x][0] = 0;
				(*frame)[y][x][1] = 0;
				(*frame)[y][x][2] = (d - 425) % 255;
			}
		}
	}
}

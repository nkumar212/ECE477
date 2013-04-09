#include "dumpdist.h"

char* ComDumpDist::char_bmp_header = "424d36100e0000000000360000002800000080020000e0010000010018000000000000100e0001000000010000000000000000000000";

ComDumpDist::ComDumpDist() : Command::Command("DumpDist")
{
	frame = (Kinect::video_buffer*)malloc(640*480*3);
	frame_count = 0;

	int c;
	uint8_t b;

	for(c = 0; c < 54; c++)
	{
		sscanf(char_bmp_header + 2* c, "%2hhx", &b);
		bmp_header[c] = b;
	}
}

int ComDumpDist::action(IDS* main)
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

	FILE* fout;
	char fname[1024];
	snprintf(fname,sizeof(fname),"frame_%d.bmp",frame_count++);
	fname[1023] = '\0';

	fout = fopen(fname,"w");
	fwrite(bmp_header,1,54,fout);
	fwrite(frame,3,640*480,fout);
	fclose(fout);
}

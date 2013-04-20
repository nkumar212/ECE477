#include "dumpvideo.h"

char* ComDumpVideo::char_bmp_header = "424d36100e0000000000360000002800000080020000e0010000010018000000000000100e0001000000010000000000000000000000";

ComDumpVideo::ComDumpVideo() : Command::Command("DumpVideo")
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

int ComDumpVideo::action(IDS* main)
{
	int x,y,i;
	long sum;
	float dist;
	Kinect::video_buffer* dframe = main->getKinect()->getVideoFrame();
	for(y = 0; y < 480; y++)
		for(x = 0; x < 640; x++)
		{
			(*frame)[479-y][x][0] = (*dframe)[y][x][2];
			(*frame)[479-y][x][1] = (*dframe)[y][x][1];
			(*frame)[479-y][x][2] = (*dframe)[y][x][0];
		}

	uint8_t d1, d0;
	uint16_t d;

	FILE* fout;
	char fname[1024];
	snprintf(fname,sizeof(fname),"frame_%d.bmp",frame_count++);
	fname[1023] = '\0';

	fout = fopen(fname,"w");
	fwrite(bmp_header,1,54,fout);
	fwrite(frame,3,640*480,fout);
	fclose(fout);
}

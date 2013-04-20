#ifndef DUMPVIDEO_H
#define DUMPVIDEO_H

#include "../Command.h"
#include "../ids.h"

class ComDumpVideo : public Command
{
	protected:
		int frame_count;
		Kinect::video_buffer* frame;
		static char* char_bmp_header;
		uint8_t bmp_header[54];
	public:
		ComDumpVideo();
		virtual int action(IDS* main);
};

#endif

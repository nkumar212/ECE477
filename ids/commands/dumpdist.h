#ifndef DUMPDIST_H
#define DUMPDIST_H

#include "../Command.h"
#include "../ids.h"

class ComDumpDist : public Command
{
	protected:
		int frame_count;
		Kinect::video_buffer* frame;
		static char* char_bmp_header;
		uint8_t bmp_header[54];
	public:
		ComDumpDist();
		virtual int action(IDS* main);
};

#endif

#include "frame.h"

ComFrame::ComFrame(std::string className) : Command::Command(className)
{
	memset(frame,0,sizeof(Kinect::video_buffer));
}

void ComFrame::setVideoSource(IDS* main)
{
	main->getKinect()->setVideoSource((uint8_t*)&frame);
}


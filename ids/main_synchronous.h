#ifndef MAIN_SYNCHRONOUS_H
#define MAIN_SYNCHRONOUS_H
#include <pthread>
#include <iostream>

#include "commandqueue.h"

int mainSynchronous(void* vids)
{
	IDS* ids = vids;
	Kinect* kinect = ids->getKinect();
	Kinect::video_buffer* vbuff;

	while(!ids->quit())
	{
		vbuff = kinect->getVideoFrame();
	}
}
#endif

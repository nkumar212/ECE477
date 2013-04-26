#ifndef DEPTHFRAME_H
#define DEPTHFRAME_H

#include <cmath>
#include <algorithm>

#include "frame.h"

class ComDepthFrame : public ComFrame
{
	public:
		ComDepthFrame();
		virtual int action(IDS* main);
};

#endif

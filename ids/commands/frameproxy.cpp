#include "frameproxy.h"

ComFrameProxy::ComFrameProxy() : Command::Command("ComFrameProxy")
{
	source = NULL;
}

int ComFrameProxy::action(IDS* main)
{
	if(source)
		return source->action(main);
	else
		return 0;
}

void ComFrameProxy::registerFrameSource(std::string src_name, ComFrame* src)
{
	registry[src_name] = src;
	if(source == NULL)
		source = src;
}

void ComFrameProxy::chooseSource(IDS* ids, std::string src_name)
{
	source = registry[src_name];
	if(source != NULL)
		source->setVideoSource(ids);
	else
		ids->getKinect()->setVideoSource(NULL);
}


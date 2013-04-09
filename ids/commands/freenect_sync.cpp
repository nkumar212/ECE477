#include "freenect_sync.h"

ComFreenectSync::ComFreenectSync() : Command::Command("FreenectSync")
{
	
}

int ComFreenectSync::action(IDS* main)
{
	main->getKinect()->process_events();
}

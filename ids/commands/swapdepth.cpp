#include "swapdepth.h"

ComSwapDepth::ComSwapDepth() : Command::Command("SwapDepth")
{
	
}

int ComSwapDepth::action(IDS* main)
{
	main->swapDepth();
}

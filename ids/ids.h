#ifndef IDS_H
#define IDS_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <set>

#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <utility>

#include "CommandQueue.h"
#include "kinect.h"
#include "minotaur.h"
#include "wall.h"

class IDS
{
	public:
		//Minos Types
		
		 #pragma pack(push,1)
		struct MinosPacket
		{
			uint8_t sync;
			uint8_t seq;
			uint8_t command;
			union
			{
				uint8_t udata8[2];
				uint16_t udata16;
				int8_t sdata8[2];
				int16_t sdata16;
			};
		};
		 #pragma pack(pop)
	protected: //Hidden Singleton Setup
		static class IDS* singleton;
		IDS();
		~IDS();

	protected: //Hidden Member attributes
		Kinect::depth_buffer* dbuffer;

		char cnc_buffer[1024];
		int cnc_desc;

		uint8_t minos_buffer[sizeof(MinosPacket)*16];
		int minos_desc;
		uint8_t minos_buffer_start, minos_buffer_end;
		uint8_t minos_seq;
		

		pthread_mutex_t minos_command_locks[256];
		MinosPacket minos_incoming[256];

		pthread_mutex_t mutex_output;
		pthread_mutex_t minos_outgoing_mutex;
		pthread_mutex_t cnc_outgoing_mutex;

		Minotaur minotaur;

	public:
		
		//Singleton constructor
		static IDS* getSingleton();

	public:
		void cnc_connect(std::string host, size_t port);
		int cnc_rawmsg(const void* msg, size_t msg_size);
		int cnc_checkmsg();
		char* cnc_getbuffer();

		void minos_connect();
		int minos_sendpacket(uint8_t command, uint16_t data = 0);
		bool minos_checkpacket(uint8_t seq);
		MinosPacket minos_getpacket(uint8_t);
		MinosPacket minos_waitpacket(uint8_t command, uint16_t data = 0);
		MinosPacket minos_packetize();
		bool minos_recv();

		Kinect* getKinect();
		CommandQueue* getCmdQueue();
		bool quit();
		void lock_output();
		void unlock_output();
		void swapDepth();
		uint64_t getDepthCount();
		uint64_t getVideoCount();
		Kinect::depth_buffer* getDepth();

		Minotaur getMinotaur();

};

#endif

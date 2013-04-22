#ifndef MINOTAUR_H
#define MINOTAUR_H

#include <cmath>
#include <stdint.h>
#include <pthread.h>
#include <stdexcept>
#include <iostream>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef PI
#define PI 3.1415926535
#endif

#define TURN_RADIUS 13.50 //Inches
#define TURN_CIRCUMFERENCE (2 * TURN_RADIUS * PI)
#define LEFT_ENCODER_TO_INCHES 4282
#define RIGHT_ENCODER_TO_INCHES 4323

typedef enum {
	POS_MINOS = 0,
	POS_KINECT = 1
} PositionPriority;

struct Minotaur
{
	public:

		//Packet for microcontroller communication, must be accurately packed
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

		//State for tracking movement of robot
		struct MinotaurState
		{
			MinotaurState();

			uint32_t timestamp;
			float x,y;
			float orient;
			uint16_t left_encoder, right_encoder;
			uint8_t ir_bank;
			uint8_t battery;

			bool valid_ts;
			bool valid_pos;
			bool valid_left_enc, valid_right_enc;
			bool valid_ir_bank, valid_battery;

			bool sensorsComplete();
		};

		//Returned to CNC server.  Must be accurately packed.
#pragma pack(push,1)
		struct MinotaurStatePacked
		{
			MinotaurStatePacked();
			MinotaurStatePacked(const MinotaurState);

			uint8_t command;
			uint32_t timestamp;
			float x,y;
			float orient;
			uint16_t left_encoder, right_encoder;
			uint8_t ir_bank;
			uint8_t battery;
		};
#pragma pack(pop)

	public: //Singleton constructor
		static Minotaur* getSingleton();

	public:
		
		//Update Incoming Packets
		bool recv();

		//External Packet commands
		int sendpacket(uint8_t command, uint16_t data = 0, bool wait_response = false);
		bool checkpacket(uint8_t seq);
		MinosPacket getpacket(uint8_t);
		MinosPacket waitpacket(uint8_t command, uint16_t data = 0);

		//Return the current best guess of physical data
		MinotaurState getState();
		void suggestState(MinotaurState sugg);
	
	protected: //Hidden Singleton Setup
		static class Minotaur* Singleton;
		Minotaur();
		~Minotaur();

	protected: //Hidden Members
		void minos_connect();
		MinosPacket packetize();
		uint32_t getMicroseconds();

	protected: //Hidden Properties
		uint8_t minos_buffer[sizeof(MinosPacket)*16];
		int minos_desc;
		uint8_t minos_buffer_start, minos_buffer_end;
		uint8_t minos_seq;

		pthread_mutex_t minos_outgoing_mutex;

		pthread_mutex_t minos_command_locks[256];
		MinosPacket minos_incoming[256];

		MinotaurState currentState;
		MinotaurState nextState;
		MinotaurState previousState;
};

#endif

#include "minotaur.h"
#include "serial.cpp"

Minotaur* Minotaur::Singleton = NULL;

Minotaur* Minotaur::getSingleton()
{
	if(Singleton)
		return Singleton;
	else
		return new Minotaur();
}

Minotaur::Minotaur()
{
	if(Singleton) throw std::runtime_error("Tried to create second instatiation of singleton class: Minotaur");
	Singleton = this;
	minos_seq = 0;
	minos_desc = 0;
	minos_buffer_start = 0;
	minos_buffer_end = 0;
	pthread_mutex_init(&minos_outgoing_mutex,NULL);

	int i;
	for(i = 0; i < 256; i++)
		pthread_mutex_init(minos_command_locks + i, NULL);

	minos_connect();
}

Minotaur::~Minotaur()
{
	Singleton = NULL;
}

uint32_t Minotaur::getMicroseconds()
{
	timespec t1;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
	return (t1.tv_sec * 1000000 + t1.tv_nsec/1000);
}

Minotaur::MinotaurState::MinotaurState()
{
	timestamp = 0;
	x = y = 0;
	orient = 0;
	left_encoder = 0;
	right_encoder = 0;
	ir_bank = 0;
	battery = 0;

	valid_ts = false;
	valid_pos = false;
	valid_left_enc = valid_right_enc = false;
	valid_ir_bank = valid_battery = false;
}

Minotaur::MinotaurStatePacked::MinotaurStatePacked()
{
	command = 0x30;
	timestamp = 0;
	x = 0;
	y = 0;
	orient = 0;
	left_encoder = 0;
	right_encoder = 0;
	ir_bank = 0;
	battery = 0;
}

Minotaur::MinotaurStatePacked::MinotaurStatePacked(const MinotaurState state)
{
	command = 0x30;
	timestamp = state.timestamp;
	x = state.x;
	y = state.y;
	orient = state.orient;
	left_encoder = state.left_encoder;
	right_encoder = state.right_encoder;
	ir_bank = state.ir_bank;
	battery = state.battery;
}

bool Minotaur::MinotaurState::sensorsComplete()
{
	return valid_left_enc && valid_right_enc && valid_ir_bank && valid_battery;
}

int Minotaur::sendpacket(uint8_t command, uint16_t data, bool wait_response)
{
	MinosPacket packet;

	uint8_t* cmd_data = (uint8_t*) &packet;

	if(minos_desc == 0)
		throw std::runtime_error("Not connected to Minos Microcontroller.  Cannot Send packet.\n");

	while(!checkpacket(++minos_seq))
		;

	if(wait_response)
		pthread_mutex_lock(&minos_command_locks[minos_seq]);

	packet.sync = 0xAA;
	packet.command = command;
	packet.udata16 = data;
	packet.seq = minos_seq;

	pthread_mutex_lock(&minos_outgoing_mutex);
	fprintf(stderr,"0x%02X 0x%04X\n",packet.command,packet.udata16);
	int count = write(minos_desc, &packet, 5);
	pthread_mutex_unlock(&minos_outgoing_mutex);

	if(count != 5)
		throw std::runtime_error("Lost Connection to Minos Microcontroller\n");

	return minos_seq;
}

bool Minotaur::recv()
{
	MinosPacket packet;
	int packets_served = 0;

	int cnt = ::recv(minos_desc, minos_buffer + minos_buffer_start, std::min<int>(sizeof(MinosPacket),sizeof(minos_buffer)-minos_buffer_start), 0);

	if(errno == EWOULDBLOCK || cnt == -1)
		return false;

	minos_buffer_end = (minos_buffer_end + cnt) % sizeof(minos_buffer);

	while((minos_buffer[minos_buffer_start] != 0xAA) && (minos_buffer_start != minos_buffer_end))
	{
		minos_buffer_start = (minos_buffer_start + 1) % sizeof(minos_buffer);
		std::cerr << "Dropping out of sync packet from Minos Microcontroller" << std::endl;
	}

	while((minos_buffer_end - minos_buffer_start + sizeof(minos_buffer)) > sizeof(MinosPacket))
	{
		while((minos_buffer[minos_buffer_start] != 0xAA) && (minos_buffer_start != minos_buffer_end))
		{
			minos_buffer_start = (minos_buffer_start + 1) % sizeof(minos_buffer);
			std::cerr << "Dropping out of sync packet from Minos Microcontroller" << std::endl;
		}

		if((minos_buffer_end - minos_buffer_start) % sizeof(minos_buffer) > sizeof(MinosPacket))
		{
			packet = packetize();
			packets_served++;

			//Better than an if statement imo
			switch(packet.command)
			{
				case 0x02:
				case 0x03:
				case 0xB1:
				case 0xB6:
				case 0xB7:
					if(!nextState.valid_ts)
					{
						nextState.timestamp = getMicroseconds();
						nextState.valid_ts = true;
					}
					break;
			}

			switch(packet.command)
			{
				case 0x01: //Drive (Echo)
					break;
				case 0x02: //Get Battery Level
					nextState.battery = packet.udata8[0];
					nextState.valid_battery = true;
					break;
				case 0x03: //Enable obstacle avoidance based on IR sensors (Echo)
					break;
				case 0xB1: //Get IR Sensor Values
					nextState.ir_bank = packet.udata8[0];
					nextState.valid_ir_bank = true;
					break;
				case 0xB6: //Get Right Encoder
					nextState.ir_bank = packet.udata16;
					nextState.valid_ir_bank = true;
					break;
				case 0xB7: //Get Left Encoder
					nextState.ir_bank = packet.udata16;
					nextState.valid_ir_bank = true;
					break;
				default:
					std::cerr << "Invalid command returned by microcontroller: " << std::hex << packet.command << " " << std::hex << packet.udata16 << std::endl;
					break;
			}
		}
	}

	if(nextState.sensorsComplete())
	{

		nextState.orient = currentState.orient;
		nextState.orient += (nextState.left_encoder - currentState.left_encoder) * LEFT_ENCODER_TO_INCHES / TURN_RADIUS;
		nextState.orient -= (nextState.right_encoder - currentState.right_encoder) * RIGHT_ENCODER_TO_INCHES / TURN_RADIUS;
		nextState.orient = fmod(nextState.orient, 2 * PI);

		nextState.x += (cos(nextState.orient) - cos(currentState.orient)) * TURN_RADIUS;
		nextState.y += (sin(nextState.orient) - sin(currentState.orient)) * TURN_RADIUS;

		nextState.valid_pos = true;
		previousState = currentState;
		currentState = nextState;
		nextState = MinotaurState();
	}

	return packets_served ? true : false;
}

bool Minotaur::checkpacket(uint8_t seq)
{
	if(pthread_mutex_trylock(&minos_command_locks[seq]) == 0)
	{
		pthread_mutex_unlock(minos_command_locks+seq);
		return true;
	}
	return false;
}

Minotaur::MinosPacket Minotaur::getpacket(uint8_t seq)
{
	MinosPacket ret;

	pthread_mutex_lock(minos_command_locks+seq);
	ret = minos_incoming[seq];
	pthread_mutex_unlock(minos_command_locks+seq);

	return ret;
}

Minotaur::MinosPacket Minotaur::packetize()
{
	MinosPacket ret;
	uint8_t* cpy = (uint8_t*)(&ret);
	int i = 0;

	while(((minos_buffer_start + i) % sizeof(minos_buffer) != minos_buffer_end) && i < sizeof(minos_buffer))
		*(cpy+i++) = minos_buffer[(minos_buffer_start + i) % sizeof(minos_buffer)];

	minos_buffer_start = (minos_buffer_start + i) % sizeof(minos_buffer);

	minos_incoming[ret.seq] = ret;

	//pthread_mutex_trylock(minos_command_locks + ret.seq);
	pthread_mutex_unlock(minos_command_locks + ret.seq);

	return ret;
}

void Minotaur::minos_connect()
{
	minos_desc = serial_init();
	minos_seq = 0;
}

Minotaur::MinotaurState Minotaur::getState()
{
	return currentState;
}

void Minotaur::suggestState(Minotaur::MinotaurState sugg)
{
	if(sugg.timestamp > currentState.timestamp && sugg.valid_pos)
	{
		currentState.x = sugg.x;
		currentState.y = sugg.y;
		currentState.orient = sugg.orient;
	}
}



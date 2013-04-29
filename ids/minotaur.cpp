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
	nextState = MinotaurState();
	currentState = MinotaurState();

	memset(minos_buffer,0,sizeof(minos_buffer));

	int i;
	for(i = 0; i < 256; i++)
		pthread_mutex_init(&(minos_command_locks[i]), NULL);

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
	return valid_left_enc && valid_right_enc && valid_ir_bank;// && valid_battery;
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
		pthread_mutex_lock(&(minos_command_locks[minos_seq]));

	packet.sync = 0xAA;
	packet.command = command;
	packet.udata16 = data;
	packet.seq = minos_seq;

	pthread_mutex_lock(&minos_outgoing_mutex);
	if(packet.command != 0xB0)
		fprintf(stderr,"0x%02X 0x%04X\n",packet.command,packet.udata16);
	int count = write(minos_desc, &packet, 5);
	pthread_mutex_unlock(&minos_outgoing_mutex);

	if(count != 5)
		std::cerr << "Lost Connection to Minos Microcontroller" << std::endl;
//		throw std::runtime_error("Lost Connection to Minos Microcontroller\n");

	return minos_seq;
}

bool Minotaur::recv()
{
	MinosPacket packet;
	int packets_served = 0;
	int32_t left_diff, right_diff;
	float left_inches, right_inches;
	float ri, ro, r;
	float pct_circum;

	int cnt = read(minos_desc, minos_buffer+minos_buffer_end, (sizeof(minos_buffer) * 2 - minos_buffer_end - 1) % sizeof(minos_buffer) + 1);
		//::recv(minos_desc, minos_buffer + minos_buffer_start, std::min<int>(sizeof(MinosPacket),sizeof(minos_buffer)-minos_buffer_start), 0);


	if(errno == EWOULDBLOCK)
	{
		std::cerr << "No data from minos (1)" << std::endl;
		return false;
	}

	if(cnt <= 0)
	{
		//std::cerr << "No data from minos (2)" << std::endl;
		return false;
	}

	if((minos_buffer_start - minos_buffer_end + sizeof(minos_buffer)) % sizeof(minos_buffer) < cnt && minos_buffer_start != minos_buffer_end)
	{
		std::cerr << "buffer settings: " << std::dec << (uint32_t)minos_buffer_start << " " << (uint32_t) minos_buffer_end << "/" << sizeof(minos_buffer) << std::endl << std::endl << std::endl;
//throw std::runtime_error("Buffer overrun occurred");
	}
	

	minos_buffer_end = (minos_buffer_end + cnt) % sizeof(minos_buffer);

/*	while((minos_buffer[minos_buffer_start] != 0xAA) && (minos_buffer_start != minos_buffer_end))
	{
		std::cerr << "Dropping out of sync packet from Minos Microcontroller " << std::hex << (uint32_t) minos_buffer[minos_buffer_start] << std::endl;
		minos_buffer_start = (minos_buffer_start + 1) % sizeof(minos_buffer);
	}*/

	while((minos_buffer_end - minos_buffer_start + sizeof(minos_buffer)) % sizeof(minos_buffer) > sizeof(MinosPacket))
	{
		while((minos_buffer[minos_buffer_start] != 0xAA) && (minos_buffer_start != minos_buffer_end))
		{
			std::cerr << "Dropping out of sync packet from Minos Microcontroller " << std::hex << (uint32_t)minos_buffer[minos_buffer_start] << std::endl;
			minos_buffer_start = (minos_buffer_start + 1) % sizeof(minos_buffer);
		}

		if((minos_buffer_end - minos_buffer_start + sizeof(minos_buffer)) % sizeof(minos_buffer) > sizeof(MinosPacket))
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
				default:
					break;
			}

			switch(packet.command)
			{
				case 0x01: //Drive (Echo)
				case 0xB0: //Get All Sensor Values (Echo)
				case 0x03: //Enable obstacle avoidance based on IR sensors (Echo)
					break;
				case 0x02: //Get Battery Level
					nextState.battery = packet.udata8[0];
					nextState.valid_battery = true;
//					std::cerr << "Recieved battery level" << std::endl;
					break;
				case 0xB1: //Get IR Sensor Values
					nextState.ir_bank = packet.udata8[0];
					nextState.valid_ir_bank = true;
//					std::cerr << "Recieved IR Sensors" << std::endl;
					break;
				case 0xB6: //Get Right Encoder
					nextState.right_encoder = packet.udata16;
					nextState.valid_right_enc = true;
//					std::cerr << "Recieved Right Encoder" << std::endl;
					break;
				case 0xB7: //Get Left Encoder
					nextState.left_encoder = packet.udata16;
					nextState.valid_left_enc = true;
					std::cerr << "Recieved left encoder value: " << packet.udata16 << std::endl;
//					std::cerr << "Recieved Left Encoder" << std::endl;
					break;
				default:
					std::cerr << "Invalid command returned by microcontroller: " << std::hex << (uint32_t)packet.command << " " << std::hex << (uint32_t)packet.udata16 << std::endl;
					break;
			}
		}
	}

	if(nextState.sensorsComplete())
	{
		if((nextState.valid_left_enc && nextState.valid_right_enc) || !currentState.valid_ts)
		{
			if(currentState.valid_ts)
			{
				left_diff = (int)nextState.left_encoder - (int)currentState.left_encoder;
				right_diff = (int)nextState.right_encoder - (int)currentState.right_encoder;
			}else{
				left_diff = 0;
				right_diff = 0;
			}

			if(right_diff > 32768)
				right_diff -= 65536;
			else if(right_diff < -32768)
				right_diff += 65536;

			if(left_diff > 32768)
				left_diff -= 65536;
			else if(left_diff < -32768)
				left_diff += 65536;
                                
                        left_inches = (float) left_diff / ENCODER_TO_INCHES;
                        right_inches = (float) right_diff / ENCODER_TO_INCHES;

			//Sanity Check, can't possibly move at a rate of 1/100 of an inch per microsecond
                        if((std::fabs(right_inches/(nextState.timestamp - currentState.timestamp)) < 1e-3) && (std::fabs(left_inches)/(nextState.timestamp-currentState.timestamp) < 1e-3) || !currentState.valid_pos)
			{
				if(left_diff == right_diff) //Straight Forward
				{
					nextState.orient = currentState.orient;
					nextState.x = currentState.x + sin(currentState.orient) * left_inches;
					nextState.y = currentState.y + cos(currentState.orient) * left_inches;
					std::cerr << "Moved forward " << left_inches << std::endl;
				}else{
					if(std::abs(left_diff) > std::abs(right_diff)) //Turning along right circle
					{
						pct_circum = (left_inches - right_inches) / TURN_CIRCUMFERENCE;
						ro = left_inches / (2 * PI * pct_circum);
						ri = right_inches / (2 * PI * pct_circum);
						r = (ro + ri) / 2;
						nextState.orient = fmod(currentState.orient - pct_circum * 2 * PI, 2 * PI);
#define TURN_CENTER_X nextState.x + r * sin(currentState.orient - PI / 2)
#define TURN_CENTER_Y nextState.y + r * cos(currentState.orient - PI / 2)
						nextState.x = TURN_CENTER_X + r * sin(nextState.orient);
						nextState.y = TURN_CENTER_Y + r * cos(nextState.orient);
#undef TURN_CENTER_X
#undef TURN_CENTER_Y			
					}else{ //Turning along left circle
						pct_circum = (right_inches - left_inches) / TURN_CIRCUMFERENCE;
						ro = right_inches / (2 * PI * pct_circum);
						ri = left_inches / (2 * PI * pct_circum);
						r = (ro + ri) / 2;
						nextState.orient = fmod(currentState.orient + pct_circum * 2 * PI, 2 * PI);
#define TURN_CENTER_X nextState.x + r * sin(currentState.orient + PI / 2)
#define TURN_CENTER_Y nextState.y + r * cos(currentState.orient + PI / 2)
						nextState.x = TURN_CENTER_X + r * sin(nextState.orient);
						nextState.y = TURN_CENTER_Y + r * cos(nextState.orient);
#undef TURN_CENTER_X
#undef TURN_CENTER_Y			
					}
					std::cerr << left_inches << " " << right_inches << " " << currentState.orient - nextState.orient << " " << ro << " " << r << " " << ri << " " << std::fabs(left_inches/(nextState.timestamp - currentState.timestamp)) << " " << std::fabs(right_inches/(nextState.timestamp - currentState.timestamp)) << std::endl;
				}
				nextState.valid_pos = true;
			}else{
				nextState.valid_pos = false;
				std::cerr << "Failed sanity check" << " " ;
				std::cerr << std::dec << left_diff << " " << right_diff;
				std::cerr << std::dec << nextState.left_encoder << " " << nextState.right_encoder << std::endl;
			}
/*		}else{
			std::cerr << "Failed invalid nextState.pos" << std::endl;*/
		}
		
		if(nextState.valid_pos)
		{
			previousState = currentState;
			currentState = nextState;
			nextState = MinotaurState();
		}
	}

	return packets_served != 0;
}

bool Minotaur::checkpacket(uint8_t seq)
{
	if(pthread_mutex_trylock(&(minos_command_locks[seq])) == 0)
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
	MinosPacket ret = MinosPacket();
	uint8_t* cpy = (uint8_t*)(&ret);
	int i = 0;

	if((minos_buffer_end - minos_buffer_start + sizeof(minos_buffer)) % sizeof(minos_buffer) < sizeof(ret))
		throw std::runtime_error("Invalid packet buffer sent to packetize");

	ret.sync = minos_buffer[(minos_buffer_start + 0) % sizeof(minos_buffer)];
	ret.seq = minos_buffer[(minos_buffer_start + 1) % sizeof(minos_buffer)];
	ret.command = minos_buffer[(minos_buffer_start + 2) % sizeof(minos_buffer)];
	ret.udata8[0] = minos_buffer[(minos_buffer_start + 3) % sizeof(minos_buffer)];
	ret.udata8[1] = minos_buffer[(minos_buffer_start + 4) % sizeof(minos_buffer)];
	minos_buffer_start = (minos_buffer_start + 5) % sizeof(minos_buffer);

	minos_incoming[ret.seq] = ret;

	pthread_mutex_trylock(minos_command_locks + ret.seq);
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



#include "ids.h"
#include "serial.cpp"

IDS* IDS::singleton = NULL;

IDS::IDS()
{
	if(singleton)
		throw std::runtime_error("Attempted to initialize two copies of singleton class: IDS");
	singleton = this;
	cnc_desc = 0;
	mutex_output = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&mutex_output,NULL);
	pthread_mutex_init(&minos_outgoing_mutex,NULL);
	pthread_mutex_init(&cnc_outgoing_mutex,NULL);
	minos_seq = 0;
	minos_desc = 0;
	minos_buffer_start = 0;
	minos_buffer_end = 0;
	int i;
	for(i = 0; i < 256; i++)
		pthread_mutex_init(minos_command_locks + i, NULL);
}

void IDS::lock_output()
{
	pthread_mutex_lock(&mutex_output);
}

void IDS::unlock_output()
{
	pthread_mutex_unlock(&mutex_output);
}

IDS* IDS::getSingleton()
{
	if(singleton) return singleton;
	else return new IDS();
}

CommandQueue* IDS::getCmdQueue()
{
	return CommandQueue::getSingleton();
}

Kinect* IDS::getKinect()
{
	return Kinect::getSingleton();
}

bool IDS::quit()
{
	return false;
}

IDS::~IDS()
{
	singleton = NULL;
	close(cnc_desc);
}

void IDS::swapDepth()
{
	dbuffer = getKinect()->getDepthFrame();
}

Kinect::depth_buffer* IDS::getDepth()
{
	return dbuffer;
}

int IDS::cnc_checkmsg()
{
	int cnt = recv(cnc_desc, cnc_buffer, 3, 0);
	cnc_buffer[cnt] = '\0';
	return cnt;
}

char* IDS::cnc_getbuffer()
{
	return cnc_buffer;
}

void IDS::cnc_connect(std::string cnc_host, size_t port)
{
	int cnc_desc;
	struct sockaddr_in serv_addr;
	struct hostent* server;
	char buff[4096];
	
	cnc_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(cnc_desc < 0)
		throw std::runtime_error("Failed to allocate a socket to the cnc server");

	bzero((char*) &serv_addr, sizeof(serv_addr));
	server = gethostbyname(cnc_host.c_str());

	if(server == NULL)
		throw std::runtime_error(std::string("Could not resolve C&C host name: ") + cnc_host);

	serv_addr.sin_family = AF_INET;
	memcpy(
		(char*) &(serv_addr.sin_addr.s_addr), 
		(char*) (server->h_addr),
		server->h_length
	      );

	serv_addr.sin_port = htons(port);
	if(connect(cnc_desc, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		throw std::runtime_error(std::string("Failed to connect to C&C Server ") + cnc_host + "\n");

	this->cnc_desc = cnc_desc;
	int flags = fcntl(cnc_desc, F_GETFL, 0);
	fcntl(cnc_desc, F_SETFL, flags & ~O_NONBLOCK);

	cnc_rawmsg("Bull:1",6);
}

int IDS::cnc_rawmsg(const void* msg, size_t msg_size)
{
	if(cnc_desc == 0)
		throw std::runtime_error("Not connected to a C&C Server.  Cannot send message.\n");

	int count = write(cnc_desc, msg, msg_size);

	if(count != msg_size)
		throw std::runtime_error("Lost Connection to C&C server\n");

	return count;
}

int IDS::minos_sendpacket(uint8_t command, uint16_t data)
{
	MinosPacket packet;

	uint8_t* cmd_data = (uint8_t*) &packet;

	if(minos_desc == 0)
		throw std::runtime_error("Not connected to Minos Microcontroller.  Cannot Send packet.\n");

	while(!minos_checkpacket(++minos_seq))
		;


	packet.sync = 0xAA;
	packet.command = command;
	packet.udata16 = data;
	packet.seq = minos_seq;

	//fprintf(stderr,"%02X %02X %02X %02X %02X\n%04X\n", cmd_data[0], cmd_data[1], cmd_data[2], cmd_data[3], cmd_data[4], data);

	pthread_mutex_lock(&minos_outgoing_mutex);
	fprintf(stderr,"0x%02X 0x%04X\n",packet.command,packet.udata16);
	int count = write(minos_desc, &packet, 5);
	//fprintf(stderr,"%02X %02X %02X %02X %02X\n%04X\n", cmd_data[0], cmd_data[1], cmd_data[2], cmd_data[3], cmd_data[4], data);
	pthread_mutex_unlock(&minos_outgoing_mutex);

	if(count != 5)
		throw std::runtime_error("Lost Connection to Minos Microcontroller\n");

	return minos_seq;
}

bool IDS::minos_recv()
{
	int cnt = recv(minos_desc, minos_buffer + minos_buffer_start, std::min<int>(sizeof(MinosPacket),sizeof(minos_buffer)-minos_buffer_start), 0);

	if(errno == EWOULDBLOCK || cnt == -1)
		return false;

	minos_buffer_end = (minos_buffer_end + cnt) % sizeof(minos_buffer);

	while((minos_buffer[minos_buffer_start] != 0xAA) && (minos_buffer_start != minos_buffer_end))
	{
		minos_buffer_start = (minos_buffer_start + 1) % sizeof(minos_buffer);
		std::cerr << "Dropping out of sync packet from Minos Microcontroller" << std::endl;
	}

	if((minos_buffer_end - minos_buffer_start + sizeof(minos_buffer)) > sizeof(MinosPacket))
	{
		minos_packetize();
		return 1;
	}

	return 0;
}

bool IDS::minos_checkpacket(uint8_t seq)
{
	if(pthread_mutex_trylock(&minos_command_locks[seq]) == 0)
	{
		pthread_mutex_unlock(minos_command_locks+seq);
		return true;
	}
	return false;
}

IDS::MinosPacket IDS::minos_getpacket(uint8_t seq)
{
	pthread_mutex_lock(minos_command_locks+seq);
	pthread_mutex_unlock(minos_command_locks+seq);

	return minos_incoming[seq];
}

IDS::MinosPacket IDS::minos_packetize()
{
	MinosPacket ret;
	uint8_t* cpy = (uint8_t*)(&ret);
	int i = 0;

	while(((minos_buffer_start + i) % sizeof(minos_buffer) != minos_buffer_end) && i < sizeof(minos_buffer))
		*cpy = minos_buffer[(minos_buffer_start + i) % sizeof(minos_buffer)];

	minos_buffer_start = (minos_buffer_start + i) % sizeof(minos_buffer);

	minos_incoming[ret.seq] = ret;

	pthread_mutex_trylock(minos_command_locks + ret.seq);
	pthread_mutex_unlock(minos_command_locks + ret.seq);

	return ret;
}

void IDS::minos_connect()
{
	minos_desc = serial_init();
	minos_seq = 0;
}

uint64_t IDS::getVideoCount()
{
	return getKinect()->getVideoCount();
}

uint64_t IDS::getDepthCount()
{
	return getKinect()->getDepthCount();
}

Minotaur IDS::getMinotaur()
{
	return minotaur;
}

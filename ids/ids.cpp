#include "ids.h"

IDS* IDS::singleton = NULL;

IDS::IDS()
{
	if(singleton)
		throw std::runtime_error("Attempted to initialize two copies of singleton class: IDS");
	singleton = this;
	sock_desc = 0;
	mutex_output = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&mutex_output,NULL);
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
	close(sock_desc);
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
	int cnt = recv(sock_desc, cnc_buffer, sizeof(cnc_buffer), 0);
	cnc_buffer[cnt] = '\0';
}

char* IDS::cnc_getbuffer()
{
	return cnc_buffer;
}

void IDS::cnc_connect(std::string cnc_host, size_t port)
{
	int sock_desc;
	struct sockaddr_in serv_addr;
	struct hostent* server;
	char buff[4096];
	
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_desc < 0)
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
	if(connect(sock_desc, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		throw std::runtime_error("Failed to connect to C&C Server\n");

	this->sock_desc = sock_desc;
	int flags = fcntl(sock_desc, F_GETFL, 0);
	fcntl(sock_desc, F_SETFL, flags & ~O_NONBLOCK);
}

int IDS::cnc_rawmsg(const void* msg, size_t msg_size)
{
	if(sock_desc == 0)
		throw std::runtime_error("Not connected to a C&C Server.  Cannot send message.\n");

	int count = write(sock_desc, msg, msg_size);

	if(count != msg_size)
		throw std::runtime_error("Lost Connection to C&C server\n");
}

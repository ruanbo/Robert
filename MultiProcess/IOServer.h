/*
 * IOServer.h
 *
 *  Created on: May 13, 2014
 *      Author: Robert
 */

#ifndef IOSERVER_H_
#define IOSERVER_H_

#include <string>

#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

class IOServer
{
private:
	std::string _address;
	int _port;

	int _listen_socket;
	int _epoll_fd;

public:
	IOServer(std::string& addr, int port=30000);
	virtual ~IOServer();

public:
	bool init();

	void run();

	void stop();
};

#endif /* IOSERVER_H_ */

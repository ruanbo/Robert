/*
 * EpollLib.h
 *
 *  Created on: Apr 15, 2014
 *      Author: Robert
 */

#ifndef EPOLLLIB_H_
#define EPOLLLIB_H_

#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>

#include "common/smart_ptr.h"
#include <list>

#define MAX_EPOLL_EVENTS 1024

struct MysgData : public smart_count
{
	std::string _data;
	int _fd;

	MysgData()
	{
		_data = "";
		_fd = 0;
	}
};
typedef smart_ptr<MysgData> MyEventPtr;


struct RecvQueue : public smart_count
{
	list<MyEventPtr> _recvs;
};

struct SendQueue : public smart_count
{
	list<MyEventPtr> _sends;
};



class EpollLib
{
private:
	int _epoll_fd;
	int _listen_sock;

	struct epoll_event* _events;

	struct MysgData _my_events[1024];


public:
	EpollLib();
	virtual ~EpollLib();

private:
	int create_epoll();

public:
	int get_epoll_fd()const;

	int get_listen_sock()const;

	bool init(const std::string& ip_addr="", int port=33333);

	int server_wait(int time_out);

	int new_client();

	int recv_data(int sock, char *recv_buf);

	int send_data(int sock, char *send_buf, int size);

	void run(int time_out);

public:
	void set_message_queue();
};

#endif /* EPOLLLIB_H_ */

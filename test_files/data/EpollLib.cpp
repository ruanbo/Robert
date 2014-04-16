/*
 * EpollLib.cpp
 *
 *  Created on: Apr 15, 2014
 *      Author: Robert
 */

#include "EpollLib.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


EpollLib::EpollLib()
{
	_epoll_fd = 0;
	_listen_sock = 0;


	_epoll_fd = create_epoll();

	_events = new epoll_event[MAX_EPOLL_EVENTS + 1];
}

EpollLib::~EpollLib()
{
	if(_listen_sock > 0)
	{
		close(_listen_sock);
	}
	if(_epoll_fd > 0)
	{
		close(_epoll_fd);
	}
}

int EpollLib::create_epoll()
{
	int epoll_fd = epoll_create(MAX_EPOLL_EVENTS);

	if(epoll_fd == -1)
	{
		cout << "epoll_create error" << endl;
	}

	return epoll_fd;
}

int EpollLib::get_epoll_fd()const
{
	return _epoll_fd;
}


bool EpollLib::init(const std::string& ip_addr, int port)
{
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(&server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if(ip_addr.empty() == true)
	{
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		server_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
	}


	_listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(_listen_sock == -1)
	{
		cout << "socket() error" << endl;
		exit(1);
	}

	if(bind(_listen_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		cout << "bind() error" << endl;
		exit(1);
	}

	if(listen(_listen_sock, 5) == -1)
	{
		cout << "listen() error" << endl;
		exit(1);
	}

	_events = new struct epoll_event[MAX_EPOLL_EVENTS];
	if(_events == NULL)
	{
		cout << "_events new error" << endl;
		exit(1);
	}

	_epoll_fd = epoll_create(MAX_EPOLL_EVENTS);

	struct epoll_event ev;
	ev.data.fd = _listen_sock;
	ev.events = EPOLLIN;

	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _listen_sock, &ev);

	return true;
}

int EpollLib::server_wait(int time_out)
{
	int nfds = epoll_wait(_epoll_fd, _events, MAX_EPOLL_EVENTS, time_out);

	return nfds;
}

int EpollLib::new_client()
{
	sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t clilen = sizeof(struct sockaddr);

	int new_sock = accept(_listen_sock, (struct sockaddr*)&client_addr, &clilen);

	struct epoll_event ev;
	ev.data.fd = new_sock;
	ev.events = EPOLLIN;

	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, new_sock, &ev);

	return new_sock;
}

int EpollLib::recv_data(int sock, char *recv_buf)
{
	char buf[1024] = {};
	int len = 0;
	int ret = 0;

	while(ret >= 0)
	{
		ret = recv(sock, buf, sizeof(buf), 0);
		if(ret <= 0)
		{
			struct epoll_event ev;
			ev.data.fd = sock;
			ev.events = EPOLLERR;
			epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, sock, &ev);
			close(sock);
			break;
		}
		else if(ret < 1024)
		{
			memcpy(recv_buf, buf, ret);
			len += ret;

			struct epoll_event ev;
			ev.data.fd = sock;
			ev.events = EPOLLOUT;
			epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, sock, &ev);
			break;
		}
		else
		{
			memcpy(recv_buf, buf, sizeof(buf));
			len += ret;
		}
	}

	return ret <= 0 ? ret : len;
}

int EpollLib::send_data(int sock, char *send_buf, int size)
{
	int len = 0;
	int ret = 0;

	while(len < size)
	{
		ret = send(sock, send_buf+len, 1024, 0);
		if(ret <= 0)
		{
			struct epoll_event ev;
			ev.data.fd = sock;
			ev.events = EPOLLERR;
			epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, sock, &ev);

			close(sock);
			break;
		}
		else
		{
			len += ret;
		}

		if(ret < 1024)
		{
			break;
		}
	}

	if(ret > 0)
	{
		struct epoll_event ev;
		ev.data.fd = sock;
		ev.events = EPOLLIN;
		epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, sock, &ev);
	}

	return ret <= 0 ? ret : len;
}

void run(int time_out)
{

}

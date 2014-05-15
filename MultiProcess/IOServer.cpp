/*
 * IOServer.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Robert
 */

#include "IOServer.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define EPOLL_SIZE 1024

IOServer::IOServer(std::string& addr, int port)
{
	_address = addr;
	_port = port;

	_listen_socket = 0;
	_epoll_fd = 0;
}

IOServer::~IOServer()
{

}

bool IOServer::init()
{
	_listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(_listen_socket == -1)
	{
		printf("socket() error");
		return false;
	}

	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_addr.s_addr = inet_addr(_address.c_str());
	server_addr.sin_port = _port;
	server_addr.sin_family = AF_INET;

	int ret = bind(_listen_socket, (sockaddr*)&server_addr, sizeof(server_addr));
	if(ret == -1)
	{
		printf("socket bind() error. \n");
		return false;
	}

	{
		int flags = fcntl(_listen_socket, F_GETFL);
		if(flags < 0)
		{
			printf("fcntl() F_GETFL error.");
			return false;
		}

		int fcntl_ret = fcntl(_listen_socket, F_SETFL, flags | O_NONBLOCK);
		if(fcntl_ret < 0)
		{
			printf("fcntl() F_SETFL error.");
			return false;
		}
	}

	ret = listen(_listen_socket, 1024);
	if(ret < 0)
	{
		printf("socker listen() error");
		return false;
	}

	_epoll_fd = epoll_create(EPOLL_SIZE);
	if(_epoll_fd < 0)
	{
		printf("epoll_create() error");
		return false;
	}
	return true;
}

void IOServer::run()
{

}

void IOServer::stop()
{

}

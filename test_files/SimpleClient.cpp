/*
 * SimpleClient.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Robert
 */

#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <boost/lexical_cast.hpp>
#include <sys/time.h>
#include <pthread.h>
#include <fcntl.h>

#include "common/TypesDef.h"

using namespace std;

const std::string SERVER_ADDR = "127.0.0.1";
const int SERVER_PORT = 1002;

static bool is_client_run = true;

void *client_thread_run(void *)
{
	int client_sock, ret;

	client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_sock == -1)
	{
		std::cout << "socket() error" << std::endl;
		return NULL;
	}


	if(false)
	{
		int flags = fcntl(client_sock, F_GETFL);
		if(flags < 0)
		{
			std::cout << "fnctl f_getfl error" << endl;
			return NULL;
		}

		int fcntl_ret = fcntl(client_sock, F_SETFL, flags | O_NONBLOCK);
		if(fcntl_ret < 0)
		{
			std::cout << "fcntl f_setfl error" << endl;
			return NULL;
		}
	}

	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);
	client_addr.sin_port = htons(0);

	if(bind(client_sock, (struct sockaddr*)&client_addr, sizeof(client_addr) ) < 0)
	{
		std::cout << "bind() error" << std::endl;
		return NULL;
	}


	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR.c_str());
	server_addr.sin_port = SERVER_PORT;

	ret = connect(client_sock, (sockaddr*)&server_addr, sizeof(server_addr));
	if(ret < 0)
	{
		std::cout << "connect() error" << std::endl;
		return NULL;
	}


//	char recv_buf[128];

	uint32 msg_id = 0;
	uint64 err_num = 0;

	static u_int16_t packet_size = 8;
	static u_int16_t packet_type = 1;

	while(is_client_run == true)
	{
		msg_id++;
		std::string msg;

		msg.append((char*)&packet_size, sizeof(packet_size));
		msg.append((char*)&packet_type, sizeof(packet_type));

		msg.append((char*)&msg_id, sizeof(msg_id));


//		msg.append("msg from client:");
//		msg.append(boost::lexical_cast<std::string>(num));

		int wret = write(client_sock, msg.c_str(), msg.length());
		if(wret < 0)
		{
			err_num ++;
		}

		usleep(10);
	}

	std::cout << "total msg num:" << msg_id << std::endl;
	std::cout << "error num :" << err_num << std::endl;
	std::cout << "right num :" << msg_id - err_num << std::endl;

	close(client_sock);

	return NULL;
}



void simple_client_test()
{
	std::string input;

	pthread_t thread_id = 0;
	if(pthread_create(&thread_id, NULL, client_thread_run, NULL) < 0)
	{
		cout << "pthread create error" << endl;
	}


	struct timeval tv;
	gettimeofday(&tv, NULL);
	uint64_t begin_us = tv.tv_sec * 1000000 + tv.tv_usec;

	while(true)
	{
		usleep(10);
		struct timeval tv;
		gettimeofday(&tv, NULL);
		uint64_t now_us = tv.tv_sec * 1000000 + tv.tv_usec;

		if(now_us - begin_us >= 5000000)
		{
			break;
		}
	}

//	while(true)
//	{
//		std::cin >> input;
//
//		if(input == "quit")
//		{
//			break;
//		}
//	}

	is_client_run = false;

	sleep(1);
}





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


const std::string SERVER_ADDR = "127.0.0.1";
const int SERVER_PORT = 1002;

void simple_client_test()
{
	int client_sock, ret;

	client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client_sock == -1)
	{
		std::cout << "socket() error" << std::endl;
		return;
	}

	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);
	client_addr.sin_port = htons(0);

	if(bind(client_sock, (struct sockaddr*)&client_addr, sizeof(client_addr) ) < 0)
	{
		std::cout << "bind() error" << std::endl;
		return;
	}

	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR.c_str());
	server_addr.sin_port = SERVER_PORT;

	ret = connect(client_sock, (sockaddr*)&server_addr, sizeof(server_addr));
	if(ret < 0)
	{
		std::cout << "connect() error" << std::endl;
		return;
	}

	std::string send_str;
//	char recv_buf[128];

	while(true)
	{
		std::cin >> send_str;

		if(send_str == "quit")
		{
			break;
		}

		write(client_sock, send_str.c_str(), send_str.length());
	}

	close(client_sock);
}







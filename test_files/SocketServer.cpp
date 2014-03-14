/*
 * SocketServer.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: root
 */


#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <bits/socket.h>
#include <arpa/inet.h>
#include <error.h>
#include <string.h>

#include "Define.h"

#define SERVER_PORT  3333
#define MAX_LISTEN   100
#define BUFF_SIZE    2048


void handle_client(int32 sock)
{
	char buffer[BUFF_SIZE];

	int received_size = -1;

	if( (received_size = recv(sock, buffer, BUFF_SIZE, 0)) < 0)
	{
		cout << "Failed to recv() from client" << endl;
	}

	cout << "msg from client:" << buffer << endl;

	if(send(sock, buffer, received_size, 0) != received_size)
	{
		cout << "failed to sned() to client" << endl;
	}

//	while(received_size > 0)
//	{
//
//		if((received_size = recv(sock, buffer, BUFF_SIZE, 0)) < 0)
//		{
//			cout << "failed to recv() others from client" << endl;
//		}
//	}

	close(sock);
}

void socket_server()
{
	int32 server_sock = 0, conn_sock = 0;

	if( (server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "create socket error." << strerror(server_sock) << endl;
		return;
	}

	struct sockaddr_in server_addr, client_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		cout << "bind socket error" << endl;
	}

	if(listen(server_sock, MAX_LISTEN) < 0)
	{
		cout << "listen sock error" << endl;
	}

	while(1)
	{
		uint32 client_len = sizeof(client_addr);

		if( (conn_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len)) < 0)
		{
			cout << "failed to accept client connection" << endl;
		}

		cout << "Client connected:" << inet_ntoa(client_addr.sin_addr) << "   port:" << client_addr.sin_port  << endl;

		handle_client(conn_sock);
	}

	close(server_sock);
}











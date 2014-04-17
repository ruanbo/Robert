/*
 * NetworkTest.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: Robert
 */

#include <sys/epoll.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <iostream>


void network_test()
{
	struct sockaddr_in server_addr;

	std::cout << "sizeof(sockaddr_in):" << sizeof(sockaddr_in) << std::endl;

	std::cout << "sizeof(server_addr): " << sizeof(server_addr) << std::endl;

	std::cout << "sizeof(&server_addr):" << sizeof(&server_addr) << std::endl;

//	bzero(&server_addr, sizeof(&server_addr));
}

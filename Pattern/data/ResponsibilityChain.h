/*
 * ResponsibilityChain.h
 *
 *  Created on: May 4, 2014
 *      Author: Robert
 */

#ifndef RESPONSIBILITYCHAIN_H_
#define RESPONSIBILITYCHAIN_H_

#include <iostream>

class Request
{
public:
	int _data;

public:
	Request()
	{
		_data = 0;
	}
	virtual ~Request()
	{

	}
};

class ChainHandler
{
protected:
	ChainHandler* _next_handler;

public:
	ChainHandler()
	{
		_next_handler = NULL;
	}
	virtual ~ChainHandler()
	{

	}
public:
	void set_up_handler(ChainHandler* handler)
	{
		_next_handler = handler;
	}

	virtual void handle_request(const Request* quest) = 0;
};

class HandlerA : public ChainHandler
{
public:
	void handle_request(const Request* quest)
	{
		if(quest->_data < 1)
		{
			std::cout << "A handled quest" << std::endl;
		}
		else
		{
			_next_handler->handle_request(quest);
		}
	}
};


class HandlerB : public ChainHandler
{
public:
	void handle_request(const Request* quest)
	{
		if(quest->_data < 3)
		{
			std::cout << "B handled quest" << std::endl;
		}
		else
		{
			_next_handler->handle_request(quest);
		}
	}
};

class HandlerZ : public ChainHandler
{
public:
	void handle_request(const Request* quest)
	{
		std::cout << "Z handled quest" << std::endl;
	}
};


void responsibility_chain_test()
{
	HandlerA* low_handle = new HandlerA();
	HandlerB* mid_handle = new HandlerB();
	HandlerZ* high_handle = new HandlerZ();

	low_handle->set_up_handler(mid_handle);
	mid_handle->set_up_handler(high_handle);

	Request* my_quest = new Request();
	my_quest->_data = 10;

	low_handle->handle_request(my_quest);

	delete my_quest;
	delete low_handle;
	delete mid_handle;
	delete high_handle;
}

#endif /* RESPONSIBILITYCHAIN_H_ */

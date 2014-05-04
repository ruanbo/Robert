/*
 * PoolDef.hpp
 *
 *  Created on: Apr 28, 2014
 *      Author: Robert
 */

#ifndef POOLDEF_HPP_
#define POOLDEF_HPP_

#include <pthread.h>
#include <cstddef>

#include <list>

#define THREAD_NUM  5

struct Message
{
	int _msg_id;
	std::string _content;
};

class PoolManager
{
public:
	bool _is_runnig;

	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
	pthread_t _woker_id[THREAD_NUM];

	std::list<Message*> _msges;

public:
	PoolManager()
	{
		_is_runnig = false;
		pthread_mutex_init(&_mutex, NULL);
		pthread_cond_init(&_cond, NULL);
	}
	~PoolManager()
	{
		pthread_mutex_destroy(&_mutex);
		pthread_cond_destroy(&_cond);
	}

	void free_all_msg()
	{
		while(_msges.empty() == false)
		{
			Message* one_msg = _msges.back();
			_msges.pop_back();
			delete one_msg;
		}
	}

};






#endif /* POOLDEF_HPP_ */

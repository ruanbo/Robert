/*
 * ThreadPool.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: root
 */

#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	_pool_manager = new PoolManager();

	for(int i=0; i<THREAD_NUM; ++i)
	{
		create_new_thread();
	}
}

ThreadPool::~ThreadPool()
{
	while(_threads.empty() == false)
	{
		TaskThread *one_thread = _threads.front();
		_threads.pop_front();

		delete one_thread;
	}

	if(_pool_manager)
	{
		delete _pool_manager;
	}
}

void ThreadPool::create_new_thread()
{
	TaskThread *thread = new TaskThread();

	if(thread->start(_pool_manager) == true)
	{
		_threads.push_back(thread);
	}
	else
	{
		delete thread;
	}
}

void ThreadPool::start()
{
	_pool_manager->_is_runnig = true;
}

void ThreadPool::stop()
{
	_pool_manager->_is_runnig = false;
}

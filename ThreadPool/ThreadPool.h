/*
 * ThreadPool.h
 *
 *  Created on: Apr 25, 2014
 *      Author: Robert
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "TaskThread.h"
#include <list>


typedef std::list<TaskThread*> ThreadList;

class ThreadPool
{
private:
	PoolManager* _pool_manager;

	ThreadList _threads;

public:
	ThreadPool();
	virtual ~ThreadPool();

private:
	void create_new_thread();

public:
	void start();

	void stop();
};







#endif /* THREADPOOL_H_ */

/*
 * ThreadPool.h
 *
 *  Created on: Apr 25, 2014
 *      Author: Robert
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "CThread.h"

#define THREAD_NUM = 10


class ThreadPool
{
private:
	int _thread_num;
	int _normal_thread_num;

	pthread_mutex_t _idle_mutex;
	pthread_mutex_t _busy_mutex;
	pthread_mutex_t _wait_mutex;
	pthread_cond_t _wait_cond;


public:
	ThreadPool();
	virtual ~ThreadPool();
};

#endif /* THREADPOOL_H_ */

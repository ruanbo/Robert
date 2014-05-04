/*
 * CThread.h
 *
 *  Created on: Apr 25, 2014
 *      Author: Robert
 */

#ifndef CTHREAD_H_
#define CTHREAD_H_

#include <pthread.h>
#include <iostream>
#include <string>
#include <cstddef>

#include "PoolDef.hpp"

enum ThreadState
{
	TS_NONE = 0,

	TS_IDLE = 1,   // 空闲
	TS_BUSY = 2,   // 忙碌
	TS_HUP = 3,    // 挂起
	TS_EXIT = 4,   // 终止

	TS_END
};


class CThread
{
private:
	pthread_t _thread_id;
	ThreadState _state;
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
protected:
	PoolManager *_pool_mamager;

public:
	CThread();
	virtual ~CThread();

public:
	bool start(PoolManager* pool_manager);
	void wait();
	bool wakeup();
	void terminate();

	void set_sate(ThreadState state);

	pthread_t get_thread_id()const;

	virtual void run() = 0;
};

#endif /* CTHREAD_H_ */

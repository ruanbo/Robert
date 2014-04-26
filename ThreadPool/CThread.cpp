/*
 * CThread.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: Robert
 */

#include "CThread.h"
#include "common/Define.h"

void *ThreadRun(void *p_thread)
{
	CThread *c_thread = (CThread*)p_thread;

	c_thread->run();

	pthread_exit(0);
}

CThread::CThread()
{
	_thread_id = 0;
	_state = TS_NONE;
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&_cond, NULL);
}

CThread::~CThread()
{
	terminate();
	pthread_mutex_destroy(&_mutex);
	pthread_cond_destroy(&_cond);
}

bool CThread::start()
{
	int ret = pthread_create(&_thread_id, NULL, &ThreadRun, (void*)this);

	if(ret != 0)
	{
		debug_info("create thread error");
		return false;
	}
	_state = TS_HUP;

	return true;
}

void CThread::wait()
{

}
bool CThread::wakeup()
{
	if(pthread_cond_signal(&_cond) == 0)
	{
		_state = TS_IDLE;
	}
	return true;
}

void CThread::terminate()
{
	if(pthread_cancel(_thread_id) == 0)
	{
		_state = TS_EXIT;
	}
	return;
}

void CThread::set_sate(ThreadState state)
{
	_state = state;
}

void CThread::run()
{

}

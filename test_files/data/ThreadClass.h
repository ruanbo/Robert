/*
 * ThreadClass.h
 *
 *  Created on: Dec 27, 2013
 *      Author: root
 */

#ifndef THREADCLASS_H_
#define THREADCLASS_H_

#include "Define.h"
#include "TimerTest.h"

#include <sys/select.h>
#include <sys/time.h>


template<typename TYPE, void(TYPE::*run)()>
void* thread_func(void* param)
{
	TYPE* This = (TYPE*)param;

	This->run();

	return NULL;
}



class ThreadClass : public smart_count
{
private:
	bool _is_running;

	pthread_t _t_pid;

	string _thread_name;

//	ModuleTimerManager _timer_manager;

public:
	ThreadClass();

	ThreadClass(const string & class_name);

	virtual ~ThreadClass();

public:
	void show_local_time();

	void timer_100ms();

	void run();

	virtual void start();

	virtual void stop();
};

typedef smart_ptr<ThreadClass> ThreadClassPtr;

#endif /* THREADCLASS_H_ */

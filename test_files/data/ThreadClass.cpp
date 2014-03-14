/*
 * ThreadClass.cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: root
 */

#include "ThreadClass.h"
#include <pthread.h>

ThreadClass::ThreadClass()
{
	_is_running = false;
	_t_pid = 0;
	_thread_name = "";
}

ThreadClass::ThreadClass(const string & class_name)
{
	_is_running = false;
	_t_pid = 0;
	_thread_name = class_name;
}

ThreadClass::~ThreadClass()
{

}

void ThreadClass::show_local_time()
{
//	struct tm *local;
	time_t t;
//	t = time(NULL);
	time(&t);

//	local = localtime(&t);

	cout << _thread_name << ". time: " << endl;

//	cout << local->tm_year << "-" << local->tm_mon << "-" << local->tm_mday << " "
//		<< local->tm_hour << ":" << local->tm_min << ":" << local->tm_sec << endl;
//
	cout << ctime(&t);
}

void ThreadClass::timer_100ms()
{
//	_timer_manager.update_now_ms(0);
}

void ThreadClass::run()
{
	cout << "start this thread_t: " << _t_pid << endl;

	_is_running = true;

	while(_is_running == true)
	{
		cout << "this thread_t: " << _t_pid << ", name:" << _thread_name << endl;

		struct timeval tv;

		tv.tv_sec = 0;
		tv.tv_usec = 100000;  // 100000

		select(0, NULL, NULL, NULL, &tv);

//		show_local_time();
	}

}


void ThreadClass::start()
{
	pthread_create(&_t_pid, NULL, thread_func<ThreadClass, &ThreadClass::run>, this);
}

void ThreadClass::stop()
{
	_is_running = false;

	cout << "stop this thread_t:" << _t_pid << ", name:" << _thread_name << endl;
}

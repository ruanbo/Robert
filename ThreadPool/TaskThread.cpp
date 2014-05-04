/*
 * TashThread.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: Robert
 */

#include "TaskThread.h"

using namespace std;


TaskThread::TaskThread()
{

}

TaskThread::~TaskThread()
{

}


void TaskThread::run()
{
	cout << "thread id:" << get_thread_id() << endl;

	while(_pool_mamager->_is_runnig)
	{
		pthread_mutex_lock(&_pool_mamager->_mutex);
		cout << "thread id:" << get_thread_id() << endl;
		usleep(1);
		pthread_mutex_unlock(&_pool_mamager->_mutex);
	}
}

/*
 * SuspendThread.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: Robert
 */

#include <pthread.h>
#include <sys/time.h>

#include <iostream>
using namespace std;

/*
 *  Node : 想做一个 thread 类， 可以自我挂起，不过下面这个还不能实现。
 *       还没找到原因。。。。。。。。。
 */


static void *thread_run(void *p);

class SuspendThread
{
public:
	pthread_t _pthread_id;
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
	bool _suspend;


public:
	SuspendThread()
	{
		_pthread_id = 0;
		pthread_mutex_init(&_mutex, NULL);
		pthread_cond_init(&_cond, NULL);
		_suspend = false;
	}

	~SuspendThread()
	{

	}

	void suspend()
	{
		if(_suspend == true)
		{
			return;
		}

		pthread_mutex_lock(&_mutex);
		_suspend = true;
		while(_suspend == true)
		{
			pthread_cond_wait(&_cond, &_mutex);
			usleep(100000);
		}
		pthread_mutex_unlock(&_mutex);
	}

	void resume()
	{
		if(_suspend == false)
		{
			return;
		}

		pthread_mutex_lock(&_mutex);
		_suspend = false;
		pthread_cond_signal(&_cond);
		pthread_mutex_unlock(&_mutex);
	}

	void start()
	{
		pthread_create(&_pthread_id, NULL, thread_run, (void*)this);
	}

	void run()
	{
		while(true)
		{
			sleep(1);
			cout << "run() " << endl;
		}
	}

};


static void *thread_run(void *p)
{
	SuspendThread *thread = (SuspendThread*)p;

	thread->run();

	return NULL;
}

void suspend_thread_test()
{
	SuspendThread *thread = new SuspendThread();

	thread->start();

	while(true)
	{
		string str;
		cin >> str;

//		flush()
		cout << " ==== str : " << str << flush << endl;
		if(str == "quit")
		{
			break;
		}
		else if(str == "suspend")
		{
			thread->suspend();
		}
		else if(str == "resume")
		{
//			cout << "6" << endl;
			thread->resume();
		}
		else
		{

		}

		sleep(1);
	}

	sleep(1);

	delete thread;
}




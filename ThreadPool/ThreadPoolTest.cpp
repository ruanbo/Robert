/*
 * ThreadPoolTest.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: Robert
 */

#include <cstdlib>
#include <pthread.h>
#include <list>
#include <stdint.h>
#include <sys/time.h>


#include <iostream>
using namespace std;


#define POOL_SIZE  10
#define TEST_TIME_US 5000000   // 5秒

struct MsgManager
{
	bool _is_running;
	pthread_t _provider_id;
	pthread_t _worker_id[POOL_SIZE];

	pthread_mutex_t _mutex;
	pthread_cond_t _cond;

	list<int> _msg;
};
static int handled_msg = 0;

static void *thread_provider(void *arg)
{
	MsgManager* msg_mngr = (MsgManager*)arg;

	cout << "provider begin. msg_mngr provider:" << msg_mngr->_provider_id << endl;

	int i = 0;
	while(msg_mngr->_is_running)
	{
		i++;
//		pthread_mutex_lock(&msg_mngr->_mutex);

		msg_mngr->_msg.push_back(i);

		pthread_cond_signal(&msg_mngr->_cond);

//		pthread_mutex_unlock(&msg_mngr->_mutex);
//		usleep(1);
	}

	pthread_exit(NULL);

	return NULL;
}

static void *thread_work(void *arg)
{
	MsgManager* msg_mngr = (MsgManager*)arg;

	pthread_t id = pthread_self();

	cout << "thread_work begin." << id << endl;

	while(msg_mngr->_is_running)
	{
		pthread_mutex_lock(&msg_mngr->_mutex);
		pthread_cond_wait(&msg_mngr->_cond, &msg_mngr->_mutex);
//		int i = msg_mngr->_msg.front();
//		cout << "pop msg:" << i << ",  id:" << id << endl;
		if(msg_mngr->_msg.empty() == false)
		{
			handled_msg++;
			msg_mngr->_msg.pop_front();
		}

		pthread_mutex_unlock(&msg_mngr->_mutex);
	}

	pthread_exit(NULL);

	return NULL;
}

void pthread_pool_test()
{
	MsgManager* msg_mngr = new MsgManager();

	pthread_mutex_init(&msg_mngr->_mutex, NULL);
	pthread_cond_init(&msg_mngr->_cond, NULL);

	msg_mngr->_is_running = true;

	for(int i=0; i<POOL_SIZE; ++i)
	{
		if(pthread_create(&msg_mngr->_worker_id[i], NULL, thread_work, (void*)msg_mngr) != 0)
		{
			cout << "thread_create error";
			exit(0);
		}
	}

	if(pthread_create(&msg_mngr->_provider_id, NULL, thread_provider, (void*)msg_mngr) != 0)
	{
		cout << "thread_create error";
		exit(0);
	}


//	string str;
//	while(true)
//	{
//		cin >> str;
//
//		if(str == "quit")
//		{
//			break;
//		}
//		sleep(1);
//	}
	struct timeval tv;
	gettimeofday(&tv, NULL);
	uint64_t begin_us = tv.tv_sec * 1000000 + tv.tv_usec;

	while(true)
	{
		usleep(10);
		struct timeval tv;
		gettimeofday(&tv, NULL);
		uint64_t now_us = tv.tv_sec * 1000000 + tv.tv_usec;

		if(now_us - begin_us >= TEST_TIME_US)
		{
			break;
		}
	}

	msg_mngr->_is_running = false;

	cout << "left msg:" << msg_mngr->_msg.size() << endl;
	cout << "handled msg:" << handled_msg << endl;

	sleep(1);

	pthread_mutex_destroy(&msg_mngr->_mutex);
	pthread_cond_init(&msg_mngr->_cond, NULL);

	delete msg_mngr;
}

/*
 * MultiThread.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: root
 */

#include "Define.h"

#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>


int g_num = 0;

void *thread_1(void *arg)
{
	for(uint32 i=0; i<100; ++i)
	{
		cout << "this is thread 1" << endl;

		struct timeval tv;

		tv.tv_sec = 0;
		tv.tv_usec = 10000;

		select(1, NULL, NULL, NULL, &tv);
		usleep(10000);
	}

	return NULL;
}

void *thread_2(void *arg)
{
	for(uint32 i=0; i<4; ++i)
	{
		cout << "This is thread 2" << endl;

		struct timeval tv;

		tv.tv_sec = 10;
		tv.tv_usec = 10000;

		select(2, NULL, NULL, NULL, &tv);
//		usleep(10000);
	}

	return NULL;
}


void multi_thread_test()
{
	pthread_t pid_1 = 0, pid_2 = 0;
//	void *pret_1, *pret_2;

	if(pthread_create(&pid_1, NULL, thread_1, NULL) != 0)
	{
		cout << "create thread_1 error" << endl;
		return;
	}

	if(pthread_create(&pid_2, NULL, thread_2, NULL) != 0)
	{
		cout << "create thread 2 error" << endl;
	}

//	if(pthread_join(pid_1, &pret_1) != 0)
//	{
//		cout << "join thread_1 error" << endl;
//		return;
//	}
//
//	if(pthread_join(pid_2, &pret_2) != 0)
//	{
//		cout << "join thread_2 error" << endl;
//		return;
//	}

	for(int j=0; j<500; ++j)
	{
		struct timeval tv;

		tv.tv_sec = 0;
		tv.tv_usec = 10000;

//		select(3, NULL, NULL, NULL, &tv);
		usleep(10000);

		cout << "in main thread" << endl;
	}


	cout << " **endl of multi_thread_test()** " << endl;
}








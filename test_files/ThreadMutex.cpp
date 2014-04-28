/*
 * ThreadMutex.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: Robert
 */

#include "common/Define.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int num = 0;

vector<int32> _test_datas;

void *thread_func1(void *)
{
	for(int i=0; i<500; ++i)
	{
		pthread_mutex_lock(&mutex);

		for(int j=0; j<5000; ++j)
		{
			num++;
			num--;
		}
		num++;
		_test_datas.push_back(num);

//		cout << "num(1) : " << num << endl;
		pthread_mutex_unlock(&mutex);

//		usleep(10);
	}
	return NULL;
}

void *thread_func2(void *)
{
	for(int i=0; i<500; ++i)
	{
		pthread_mutex_lock(&mutex);

		for(int j=0; j<5000; ++j)
		{
			num++;
			num--;
		}

		num++;
		_test_datas.push_back(num);
//		cout << "num(2) :" << num << endl;

		pthread_mutex_unlock(&mutex);
//		usleep(10);
	}
	return NULL;
}


void thread_mutex_test()
{
	pthread_t pid1;
	pthread_t pid2;

	pthread_mutex_init(&mutex, NULL);

	if(pthread_create(&pid1, NULL, thread_func1, NULL) != 0)
	{
		cout << "pthread_create() error" << endl;
		return;
	}
	if(pthread_create(&pid2, NULL, thread_func2, NULL) != 0)
	{
		cout << "pthread_create() error" << endl;
		return;
	}

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);

	pthread_mutex_destroy(&mutex);

	size_t len = _test_datas.size();

	for(size_t i=0; i<len; ++i)
	{
		printf("%d  ", _test_datas[i]);
		if(i % 20 == 0)
		{
			printf("\n");
		}
	}
}

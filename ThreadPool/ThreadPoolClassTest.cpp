/*
 * ThreadPoolClassTest.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: Robert
 */


#include "ThreadPool.h"

#include <iostream>
using namespace std;



void thread_pool_class_test()
{
	ThreadPool *thread_pool = new ThreadPool();

	thread_pool->start();

	string str;
	while(true)
	{
		cin >> str;

		if(str == "quit")
		{
			break;
		}
		sleep(1);
	}

	delete thread_pool;
}





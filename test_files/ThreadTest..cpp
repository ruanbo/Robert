/*
 * ThreadTest..cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: root
 */


#include "data/ThreadClass.h"



void thread_class_test()
{
	vector<ThreadClassPtr> center;

	ThreadClassPtr one_thread = new ThreadClass("thread_1");
	center.push_back(one_thread);

	ThreadClassPtr two_thread = new ThreadClass("thread_2");
	center.push_back(two_thread);


	foreach_constcontainer(iter, center)
	{
		ThreadClassPtr thread = *iter;

		thread->start();
	}

	string is_quit = "";

	while(1)
	{
		sleep(1);

		cin >> is_quit;

		if(is_quit == "quit")
		{
			break;
		}

	}

	foreach_constcontainer(iter, center)
	{
		ThreadClassPtr thread = *iter;

		thread->stop();
	}



	sleep(3);
}


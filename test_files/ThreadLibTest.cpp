/*
 * ThreadLibTest.cpp
 *
 *  Created on: Apr 9, 2014
 *      Author: root
 */



#include "data/ThreadLib.h"


volatile bool is_quit_all_task = false;


class Task1 : public ThreadLib
{
private:
	void run()
	{
		while(is_quit_all_task == false)
		{
			cout << "I am task 1" << endl;
			ThreadLib::sleep(1000);
		}
	}
};

class Task2 : public ThreadLib
{
private:
	void run()
	{
		while(is_quit_all_task == false)
		{
			cout << "I am task 2" << endl;
			ThreadLib::sleep(400);
		}
	}
};


void thread_lib_test()
{
	Task1 task1;
	Task2 task2;

	task1.start();
	task2.start();


	string input_str;

	while(true)
	{
		cin >> input_str;

		if (input_str == "quit")
		{
			break;
		}
		sleep(1);
	}

	is_quit_all_task = true;
	sleep(3);
}

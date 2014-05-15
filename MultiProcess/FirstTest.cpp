/*
 * FirstTest.cpp
 *
 *  Created on: May 8, 2014
 *      Author: Robert
 */

#include "MultiProcessHeader.h"



void multi_process_first()
{
	pid_t child_1=0, child_2=0;

	child_1 = fork();
//	child_2 = fork();

	cout << "child:" << child_1 << endl;

	if(child_1 == -1)
	{
		cout << "fork() error" << endl;
	}
	else if(child_1 == 0)
	{
		cout << "in child. getpid():" << getpid() << endl;

		process_entry(PT_LOGIN);
	}
	else
	{
		process_entry(PT_LOGIC);
		cout << "in father. getpid():" << getpid() << endl;
	}

//	cout << "end of multi_process_first()" << endl;
}


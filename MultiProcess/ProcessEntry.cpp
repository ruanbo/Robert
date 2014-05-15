/*
 * ProcessEntry.cpp
 *
 *  Created on: May 8, 2014
 *      Author: Robert
 */


#include "MultiProcessHeader.h"


void process_entry(ProcessType type)
{
	while(true)
	{
		if(type == PT_LOGIN)
		{
			cout << "I'm Login" << endl;
		}
		else if(type == PT_LOGIC)
		{
			cout << "I'm Logic" << endl;
		}
		else
		{
			cout << "who am I" << endl;
		}

//		usleep(10000);
		sleep(1);
	}

}




/*
 * TashThread.h
 *
 *  Created on: Apr 28, 2014
 *      Author: Robert
 */

#ifndef TASHTHREAD_H_
#define TASHTHREAD_H_

#include "CThread.h"

class TaskThread : public CThread
{
public:
	TaskThread();
	virtual ~TaskThread();

public:

	virtual void run();
};



#endif /* TASHTHREAD_H_ */

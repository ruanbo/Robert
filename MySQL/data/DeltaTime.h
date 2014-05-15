/*
 * DeltaTime.h
 *
 *  Created on: May 15, 2014
 *      Author: Robert
 */

#ifndef DELTATIME_H_
#define DELTATIME_H_

#include <string>
#include <sys/types.h>
#include <sys/time.h>

class DeltaTime
{
private:
	int64_t _begin;
	int64_t _end;
	std::string _info;

private:
	DeltaTime();
public:
	DeltaTime(const std::string& info="default");

	virtual ~DeltaTime();

	int64_t get_now_us();
};

#endif /* DELTATIME_H_ */

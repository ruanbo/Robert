/*
 * DeltaTime.cpp
 *
 *  Created on: May 15, 2014
 *      Author: Robert
 */

#include "DeltaTime.h"
#include <iostream>


DeltaTime::DeltaTime(const std::string& info)
{
	_begin = get_now_us();
	_end = 0;
	_info = info;
}

DeltaTime::~DeltaTime()
{
	_end = get_now_us();

	std::cout << _info << " time(us):" << (_end - _begin) << std::endl;
}


int64_t DeltaTime::get_now_us()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

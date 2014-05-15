/*
 * CommonFunc.cpp
 *
 *  Created on: May 14, 2014
 *      Author: Robert
 */

#include <sys/time.h>
#include <sys/types.h>
#include <stddef.h>

int64_t get_now_us()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return (tv.tv_sec * 1000000 + tv.tv_usec);
}


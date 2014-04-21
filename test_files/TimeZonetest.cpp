/*
 * TimeZonetest.cpp
 *
 *  Created on: Apr 21, 2014
 *      Author: Robert
 */

#include <sys/time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



void time_zone_test()
{

	setenv("TZ", "GMT-7", 1);

	tzset();

	printf("daylight : %d \n", daylight);
	printf("timezone: %ld \n", timezone);

	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);

	printf("now secs: %ld", (long int)tv.tv_sec);

}

/*
 * va_list_test.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: root
 */

#include <stdarg.h>
#include "Define.h"

void va_list_test1(int start, ...)
{
	va_list arg_ptr;
	int arg_value = start;
	int arg_count = 0;

	va_start(arg_ptr, start);

	do
	{
		++arg_count;
		debug_info("the %d arg:%d", arg_count, arg_value);
		arg_value = va_arg(arg_ptr, int);
	}while(arg_value != -1);
}

void va_list_test()
{
	va_list_test1(100,1,9,-1);

	va_list_test1(100,4,11, 999,-1);
}




/*
 * main.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: root
 */


#include "Define.h"

#include "Func.h"

int main()
{
	debug_info("boost version: %d", BOOST_VERSION);

	all_test_func_entry();


	return 0;
}

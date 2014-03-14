/*
 * Module.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: root
 */

#include "Module.h"



Module::Module()
{
	_module_id = 0;
	_module_name = "";

	_thread_id = 0;
}

Module::~Module()
{

}


void * Module::on_start(void *args)
{

	return NULL;
}

void Module::start()
{
//	pthread_create(&_thread_id, NULL, on_start, NULL);
}

void Module::stop()
{

}


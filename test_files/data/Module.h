/*
 * Module.h
 *
 *  Created on: Dec 9, 2013
 *      Author: root
 */

#ifndef MODULE_H_
#define MODULE_H_

#include "Define.h"

#include <pthread.h>

class Module : smart_count
{
private:
	uint32 _module_id;
	string _module_name;

	pthread_t _thread_id;

public:
	Module();
	virtual ~Module();

public:
	void set_module_id();

	void set_module_name();

	string get_module_name()const;

public:
	void *on_start(void *args);

	void start();

	void stop();
};

typedef smart_ptr<Module> ModulePtr;



#endif /* MODULE_H_ */

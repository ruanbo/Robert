/*
 * Singleton.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: Robert
 */

#include "Singleton.h"

#include <sys/types.h>

#include <pthread.h>
#include <iostream>

Singleton0* Singleton0::_instance = new Singleton0();

Singleton0::Singleton0()
{
	std::cout << "Singleton0()" << std::endl;
}

Singleton0::~Singleton0()
{
	std::cout << "~Singleton0()" << std::endl;
}

Singleton0* Singleton0::get_instance()
{
	return _instance;
}


void Singleton0::show()
{
	std::cout << "a show of 0" << std::endl;
}

/////////

Singleton1* Singleton1::_instance = NULL;

Singleton1::Singleton1()
{
	std::cout << "Singleton1()" << std::endl;
}

Singleton1::~Singleton1()
{
	std::cout << "~Singleton1()" << std::endl;
}

Singleton1* Singleton1::get_instance()
{
	if(_instance == NULL)
	{
		_instance = new Singleton1();
	}

	return _instance;
}

void Singleton1::show()
{
	std::cout << "a show of 1" << std::endl;
}


//////////////////////

Singleton2* Singleton2::_instance = NULL;

Singleton2::Singleton2()
{
	std::cout << "Singleton2()" << std::endl;
}

Singleton2::~Singleton2()
{
	std::cout << "~Singleton2()" << std::endl;
}

Singleton2* Singleton2::get_instance()
{
	if(_instance == NULL)
	{
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		int ret = pthread_mutex_lock(&mutex);
		if(ret == 0)
		{
			std::cout << "mutex lock success" << std::endl;
		}

		if(_instance == NULL)
		{
			_instance = new Singleton2();
		}

		pthread_mutex_unlock(&mutex);
		pthread_mutex_destroy(&mutex);
	}

	return _instance;
}


void Singleton2::show()
{
	std::cout << "a show of 2" << std::endl;
}





////////////////////
Singleton3::Singleton3()
{
	std::cout << "Singleton3()" << std::endl;
}

Singleton3::~Singleton3()
{
	std::cout << "~Singleton3()" << std::endl;
}

Singleton3* Singleton3::get_instance()
{
	static Singleton3 instance;

	return &instance;
}

void Singleton3::show()
{
	std::cout << "a show of 3" << std::endl;
}



/////////
Singleton4* Singleton4::_instance = NULL;
Singleton4::Garbage Singleton4::_garbage = Singleton4::Garbage();

Singleton4::Singleton4()
{
	std::cout << "Singleton4()" << std::endl;
}

Singleton4::~Singleton4()
{
	std::cout << "~Singleton4()" << std::endl;
}

Singleton4* Singleton4::get_instance()
{
	if(_instance == NULL)
	{
		_instance = new Singleton4();
	}
	return _instance;
}

void Singleton4::show()
{
	std::cout << "show of 4" << std::endl;
}









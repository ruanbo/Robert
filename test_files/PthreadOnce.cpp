/*
 * PthreadOnce.cpp
 *
 *  Created on: May 12, 2014
 *      Author: Robert
 */


#include "common/Define.h"
#include <pthread.h>
#include <boost/noncopyable.hpp>

template<typename T>
class Singleton : boost::noncopyable
{
private:
	static pthread_once_t _ponce;
	static T* _value;

public:
	static T& instance()
	{
		pthread_once(&_ponce, &Singleton::init);
		return *_value;
	}

	static void init()
	{
		_value = new T();
	}
};

template<typename T>
pthread_once_t Singleton<T>::_ponce = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::_value = NULL;

















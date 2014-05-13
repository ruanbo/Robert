/*
 * ExceptionTest.cpp
 *
 *  Created on: May 12, 2014
 *      Author: Robert
 */

#include "common/Define.h"


class MyException : protected exception
{
private:
	string _msg;
public:
	MyException(const string& msg="this is my exception")
	{
		_msg = msg;
	}
	virtual ~MyException() throw()
	{

	}
	virtual const char *what()const throw()
	{
		return _msg.c_str();
	}
};

void exception_test()
{
	try {
		throw exception();
	}
	catch (exception& e) {
		cout << e.what();
	}
}

/*
 * PointerTest.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: Robert
 */

#include "common/Define.h"

class OS
{
private:
	int _data;
public:
	OS(int data) { _data = data; }
	virtual ~OS()
	{

	}

public:
	void install()
	{
		cout << "data:" << _data << endl;
	}
	int get_data()const
	{
		return _data;
	}
};

class Computer
{
private:
	OS *_os;
public:
	Computer(OS *os)
	{
		_os = new OS(os->get_data());
		*_os = *os;
	}
	~Computer()
	{
		if(_os) delete _os;
	}

public:
	void begin()
	{
		_os->install();
	}
};

void pointer_test()
{
	OS *os = new OS(10);

	Computer *computer = new Computer(os);
	computer->begin();

	delete computer;
	delete os;

}



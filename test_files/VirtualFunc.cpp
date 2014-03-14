/*
 * VirtualFunc.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: root
 */

#include "Define.h"

class Base: public smart_count
{
protected:
	uint32 _data;

public:
	Base()
	{
		_data = 0;
	}

	virtual ~Base()
	{

	}

public:
	void set_data(uint32 data)
	{
		_data = data;
	}

	uint32 get_data()const
	{
		return _data;
	}

	virtual void show_data()const
	{
		cout << "Base data: " << _data << endl;
	}
};

typedef smart_ptr<Base> BasePtr;


class Driver1 : public Base
{

public:
	Driver1()
	{

	}

	~Driver1()
	{

	}

	void show_data()const
	{
		cout << "Driver1, data: " << _data << endl;
	}
};

typedef smart_ptr<Driver1> Driver1Ptr;


class Driver2 : public Base
{

public:
	Driver2()
	{

	}

	void show_data()const
	{
		cout << "Driver2, data: " << _data << endl;
	}
};

typedef smart_ptr<Driver2> Driver2Ptr;



void virtual_class_func_test()
{
	BasePtr base_p = new Base();
	base_p->set_data(0);
	base_p->show_data();

	BasePtr d1_p = new Driver1();
	d1_p->set_data(1);
	d1_p->show_data();

	BasePtr d2_p = new Driver2();
	d2_p->set_data(2);
	d2_p->show_data();


}




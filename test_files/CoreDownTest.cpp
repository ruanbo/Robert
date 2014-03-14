/*
 * CoreDownTest.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: root
 */



#include "Define.h"


class CoreDown
{
private:
	int32 _data;

public:
	CoreDown()
	{
		_data = 0;
	}

	virtual ~CoreDown()
	{

	}

public:
	void set_data(int32 data)
	{
		_data = data;
	}

	int32 get_data()const
	{
		return _data;
	}
};

void core_down_1()
{
	CoreDown* p_CoreData = new CoreDown();

	p_CoreData->set_data(100);

	cout << p_CoreData->get_data() << endl;
}




void core_down_test()
{
	core_down_1();
}


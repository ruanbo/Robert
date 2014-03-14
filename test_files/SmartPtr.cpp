/*
 * SmartPtr.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: root
 */


#include "Define.h"


class CSmart : public smart_count
{
private:
	uint32 _id;
	string _name;

public:
	CSmart()
	{
		_id = 0;
		_name = "";
	}

	virtual ~CSmart()
	{

	}

	void set_id(uint32 id)
	{
		_id = id;
	}

	uint32 get_id()const
	{
		return _id;
	}

	void set_name(const string & name)
	{
		_name = name;
	}

	string get_name()const
	{
		return _name;
	}


};

typedef smart_ptr<CSmart> CSmartPtr;





void smart_ptr_test()
{
	CSmartPtr one_ptr = new CSmart();

	one_ptr->set_id(1001);
	one_ptr->set_name("Robert");

	cout <<  one_ptr->get_id() << "    " << one_ptr->get_name() << endl;
}









/*
 * C11Test.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Robert
 */

#include "common/Define.h"

#include <boost/format.hpp>

class CMutable
{
private:
	mutable int _data;
public:
	CMutable(int data)
	{
		_data = data;
	}
	int get_data(int data)const
	{
		_data = data;
		return _data;
	}
};

void mutable_test()
{
	CMutable m(1);

	int data = m.get_data(10);

	cout << "data:" << data << endl;
}


//==============
class CExplicit
{
private:
	int _data;
public:
	CExplicit(int data) : _data(data)
	{

	}

	void show()const
	{
		cout << "_data:" << _data << endl;
	}
};

void explicit_test()
{
	CExplicit explt(10);
	explt.show();

	CExplicit explt2 = 100;
	explt2.show();
}






// ==========
void boost_format_test()
{
	cout << (boost::format("id:%d, name:%s") % 100 % "robert") << endl;
}

// == test..

void c11_test()
{
//	mutable_test();

//	explicit_test();

	boost_format_test();
}

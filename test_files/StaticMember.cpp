/*
 * StaticMember.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: root
 */

#include "Define.h"

class Simple : smart_count
{
private:
	uint32 _data;

public:
	static void show_data()
	{
//		cout << "data:" << _data << endl;
	}

};



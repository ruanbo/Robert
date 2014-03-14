/*
 * BoostTest.cpp
 *
 *  Created on: Dec 27, 2013
 *      Author: root
 */


#include "Define.h"


void is_all_test()
{
	string str_1 = "124t56";

	bool is_all_digit = boost::all(str_1, boost::is_digit());

	cout << "str.size():" << str_1.size() << endl;

	cout << "is_all_digit:" << is_all_digit << endl;
}


void convert_str_num()
{
	 vector<uint32> num_v = boost::assign::list_of(1)(2)(3)(4)(5);

	show_coll(num_v);

	string convert_str;
	foreach_constcontainer(iter, num_v)
	{
		convert_str += (boost::lexical_cast<string>(*iter) + "  ");
	}

	cout << "convert_str:" << convert_str << endl;
}




void boost_test()
{
	convert_str_num();
}

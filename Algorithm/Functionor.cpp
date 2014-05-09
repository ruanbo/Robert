/*
 * Functionor.cpp
 *
 *  Created on: May 6, 2014
 *      Author: Robert
 */

#include "AlgorithmHeaderFile.h"

template<typename Iter, typename Func>
void my_for_each(Iter begin, Iter end, Func func)
{
	for(; begin != end; ++begin)
	{
		func(*begin);
	}
}

void display_f(int i)
{
	cout << "functionor:" << i << endl;
}

bool comp(int i, int j)
{
	return i > j;
}

// 仿函数测试
void functionor_test()
{
	vector<int> array;
	array.push_back(1);
	array.push_back(9);
	array.push_back(3);
	array.push_back(5);
	array.push_back(7);
	array.push_back(1);
	array.push_back(6);
	array.push_back(6);

	sort(array.begin(), array.end(), comp);

	my_for_each(array.begin(), array.end(), display_f);
}


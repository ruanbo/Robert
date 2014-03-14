/*
 * TemplateTest.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: root
 */


#include "Define.h"


template <class T>
void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}



/*
 * IntType.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: root
 */

#include "Define.h"


void int_type_tests()
{
	PyObject *obj;

	obj = PyInt_FromSize_t(10);

	cout << "is int:" << PyInt_Check(obj) << endl;

}



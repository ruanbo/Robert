/*
 * FirstTest.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: root
 */

#include "Define.h"


int set_all(PyObject *target, PyObject *item)
{
	int i, n;

	n = PyObject_Length(target);
	if(n < 0)
	{
		return -1;
	}

	for(i=0; i<n; ++i)
	{
		PyObject *index = PyInt_FromLong(i);
		if(index == NULL)
		{
			return -1;
		}

		if(PyObject_SetItem(target, index, item) < 0)
		{
			Py_DECREF(index);
			return -1;
		}
		Py_DECREF(index);
	}

	return 0;
}

void common_funcs()
{
	PyObject *tuple, *list;

	tuple = Py_BuildValue("(iis)", 1, 2, "three");
	list = Py_BuildValue("[iis]", 1, 2, "three");

	Py_Main(0, NULL);

//	Py_TTA
}

long sum_list(PyObject *list)
{
	long total = 0;

	PyObject *item;

	int n = PyList_Size(list);
	if(n < 0)
	{
		return -1;
	}

	for(int i=0; i<n; ++i)
	{
		item = PyList_GetItem(list, i);
		if(PyInt_Check(item) == false)
		{
			continue;
		}

		total += PyInt_AsLong(item);
	}

	return total;
}


long sum_sequence(PyObject *sequence)
{
	long total = 0;
	PyObject *item;

	int n = PySequence_Size(sequence);
	if(n < 0)
	{
		return -1;
	}

	for(int i=0; i<n; ++i)
	{
		item = PySequence_GetItem(sequence, i);
		if(item == NULL)
		{
			return -1;
		}

		if(PyInt_Check(item) == true)
		{
			total += PyInt_AsLong(item);
		}

		Py_DECREF(item);
	}

	return total;
}






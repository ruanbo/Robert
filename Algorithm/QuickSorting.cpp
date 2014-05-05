/*
 * Sorting.cpp
 *
 *  Created on: May 4, 2014
 *      Author: Robert
 */


#include "AlgorithmHeaderFile.h"

void swap(vector<int>& array, int pos1, int pos2)
{
	int temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;
}

int quick_sort(vector<int>& array, int left, int right)
{
	if(left >= right)
	{
		return -1;
	}

	int key = array[left];
	int mid_pos = left;
	int curse = left+1;

	while(curse <= right)
	{
		if(array[curse] <= key)
		{
			array[mid_pos] = array[curse];
			array[curse] = array[mid_pos+1];
			mid_pos++;
		}
		curse++;
	}
	array[mid_pos] = key;


	if(mid_pos-1 > left)
	{
		quick_sort(array, left, mid_pos-1);
	}
	if(right > mid_pos+1)
	{
		quick_sort(array, mid_pos+1, right);
	}

	return mid_pos;
}

void quick_sort_test()
{
	vector<int> array;
	array.push_back(1);
	array.push_back(9);
	array.push_back(3);
	array.push_back(5);
	array.push_back(7);
	array.push_back(1);

	quick_sort(array, 0, array.size()-1);

	cout << "after sort:";

	foreach_constcontainer(iter, array)
	{
		cout << *iter << " ";
	}

}


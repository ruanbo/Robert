/*
 * MergeSorting.cpp
 *
 *  Created on: May 5, 2014
 *      Author: Robert
 */

#include "AlgorithmHeaderFile.h"



void merge(vector<int>& array, int left, int mid, int right, vector<int>& temp)
{
	if(array.empty()==true || mid<left || mid>right || left>=right)
	{
		return;
	}
	int i=left, j=mid+1, temp_idx = left;

	while(i<=mid && j<=right)
	{
		temp[temp_idx++] = array[i]<array[j] ? array[i++] : array[j++];
	}

	while(i<=mid)
	{
		temp[temp_idx++] = array[i++];
	}
	while(j<=right)
	{
		temp[temp_idx++] = array[j++];
	}


	printf("[%d %d %d] \n", left, mid, right);

	cout << "before merge: ";
	for(int idx=left; idx<=right; ++idx)
	{
		cout << array[idx] << "  ";
	}

	for(int idx=left; idx<=right; ++idx)
	{
		array[idx] = temp[idx];
	}

	cout << endl << "after merge: ";
	for(int idx=left; idx<=right; ++idx)
	{
		cout << array[idx] << "  ";
	}
	cout << endl << endl;
}


void merge_sort(vector<int>& array, int left, int right, vector<int>& temp)
{
	if(left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;

	printf("[%d - %d] \n", left, right);
	{
		merge_sort(array, left, mid, temp);
		merge_sort(array, mid+1, right, temp);
		merge(array, left, mid, right, temp);
	}
}



void merge_sort_test()
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

	vector<int> temp;
	temp.reserve(array.size());

	merge_sort(array, 0, array.size()-1, temp);

	cout << "after merge sort:";
	foreach_constcontainer(iter, array)
	{
		cout << *iter << " ";
	}
}


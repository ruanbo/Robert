/*
 * Heap.cpp
 *
 *  Created on: May 6, 2014
 *      Author: Robert
 */


#include "AlgorithmHeaderFile.h"

template<typename Func>
void m_heap(vector<int>& array, size_t first, size_t last, Func comp)
{
	if(array.size()<last || first >= last) return;

	size_t child = 0;
	size_t parent = 0;

	for(size_t i=(first+last)/2; i<=last; ++i)
	{
		child = i;

		while(child > first)
		{
			parent = (child-1) / 2;
			if(comp(array[child], array[parent]))
			{
				swap(array[child], array[parent]);
			}
			child = parent;
		}
	}
}

void heap_sort(vector<int>& array)
{
	size_t index = array.size() - 1;
	while(index > 0)
	{
		m_heap(array, (size_t)0, index, greater<int>());

		swap(array[0], array[index]);

		index--;
	}
}

void display(int i)
{
	cout << i << endl;
}

void heap_test()
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

//	make_heap(array, 0, array.size()-1);

//	for_each(array.begin(), array.end(), greater<int> );
//	make_heap(array.begin(), array.end(), greater<int>());

//	m_heap(array, 0, array.size()-1, greater<int>());
//	heap_sort(array);

	for_each(array.begin(), array.end(), display);

	cout << "after heap:";
	foreach_constcontainer(iter, array)
	{
		cout << *iter << " ";
	}
}



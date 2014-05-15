/*
 * Define.h
 *
 *  Created on: Dec 6, 2013
 *      Author: root
 */

#ifndef DEFINE_H_
#define DEFINE_H_


//  system headers
#include <iostream>
using namespace std;

#include <sys/time.h>

#include <vector>
#include <map>
#include <set>
#include <list>

#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

#include <boost/bind.hpp>
#include <boost/version.hpp>

//  headers defined by programer
#include "TypesDef.h"

#include "smart_ptr.h"



//for python2.6
#include "python2.6/Python.h"




template<typename T>
struct auto_container
{
	typedef typename T::iterator iterator;
	typedef typename T::const_iterator const_iterator;
};

#define foreach_constcontainer(i, c) for(auto_container<typeof(c)>::const_iterator i=c.begin(); i!=c.end(); ++i)

#define foreach_iterator(i, b, e) for( typeof(b) i=b; i!=e; ++i)




#ifdef LOCAL_DEBUG
	#define SYS_DEBUG_INFO true
#else
	#define SYS_DEBUG_INFO false
#endif

#define debug_info(...) if(SYS_DEBUG_INFO){printf(__VA_ARGS__); printf("\n");}




template<typename T>
void show_coll(const T & coll)
{
	typename T::const_iterator it = coll.begin();
	for(; it!=coll.end(); ++it)
	{
		cout << *it << "  ";
	}
	cout << endl;
}

int64_t get_now_us();

//
//template<typename T>
//void swap(vector<T>& array, int pos1, int pos2)
//{
//	T temp = array[pos1];
//
//	array[pos1] = array[pos2];
//	array[pos2] = temp;
//}





#endif /* DEFINE_H_ */

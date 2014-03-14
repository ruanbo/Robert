/*
 * MultiContainer.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: root
 */


#include "Define.h"

#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost;
using namespace boost::multi_index;


class Sworn : public smart_count
{
public:
	uint32 _id;
	string _name;

public:
	Sworn()
	{
		_id = 0;
		_name = "";
	}

	~Sworn()
	{

	}

public:
	uint32 get_id()const
	{
		return _id;
	}

	string get_name()const
	{
		return _name;
	}

};

typedef smart_ptr<Sworn> SwornPtr;

typedef multi_index_container<SwornPtr,
		indexed_by<
			hashed_unique<const_mem_fun<Sworn, uint32, &Sworn::get_id> >,
			hashed_non_unique<const_mem_fun<Sworn, string, &Sworn::get_name> >
				>
				> Sworns;

typedef Sworns::nth_index<0>::type IdSworns;
typedef Sworns::nth_index<1>::type NameSworns;

class SwornHelper : public smart_count
{
private:
	Sworns _sworns;

public:
	SwornHelper()
	{

	}

	~SwornHelper()
	{

	}

public:
	void add_sworn(const SwornPtr & sworn)
	{
		_sworns.insert(sworn);
	}

	SwornPtr get_sworn(const string & sworn_name)const
	{
		NameSworns::const_iterator it = _sworns.get<1>().find(sworn_name);

		if(it != _sworns.get<1>().end())
		{
			return *it;
		}
		return NULL;
	}

	bool is_name_used(const string & sworn_name)const
	{
		NameSworns::const_iterator it = _sworns.get<1>().find(sworn_name);

		if(it != _sworns.get<1>().end())
		{
			return true;
		}
		return false;
	}

	void show_sworns()const
	{
		for (Sworns::iterator iter = _sworns.begin(); iter != _sworns.end(); ++iter)
		{
			SwornPtr sworn = *iter;

			cout << "id:" << sworn->_id << ", name:" << sworn->_name << endl;
		}
	}
};


void multi_cotainer_test()
{
	SwornHelper helper;

	SwornPtr sworn_1 = new Sworn();
	sworn_1->_id = 1;
	sworn_1->_name = "sworn_1";

	helper.add_sworn(sworn_1);

	SwornPtr sworn_2 = new Sworn();
	sworn_2->_id = 2;
	sworn_2->_name = "sworn_1";

	helper.add_sworn(sworn_2);

	helper.show_sworns();



	string name = "sworn_1";

	cout << endl << "is " << name << " used:" << helper.is_name_used(name) << endl << endl;

	SwornPtr find_sworn = helper.get_sworn(name);
	cout << "find_sworn._name:" << find_sworn->_name << endl;
}










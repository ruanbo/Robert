/*
 * Flyweight.h
 *
 *  Created on: Apr 24, 2014
 *      Author: Robert
 */

#ifndef FLYWEIGHT_H_
#define FLYWEIGHT_H_


#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Flyweight
{
private:
	string _intrinsic_state;

public:
	virtual ~Flyweight();
protected:
	Flyweight(const string& intrinsic_state)
	{
		_intrinsic_state = intrinsic_state;
	}

public:
	virtual void Operation(const string& extrinsic_state) = 0;

	string get_intrinsic_state()
	{
		return _intrinsic_state;
	}
};

class ConcreteFlyweight : public Flyweight
{
public:
	ConcreteFlyweight(const string& intrinsic_state) : Flyweight(intrinsic_state)
	{

	}
	~ConcreteFlyweight()
	{

	}

public:
	void Operation(const string& extrinsic_state)
	{
		cout << get_intrinsic_state() << endl;
		cout << extrinsic_state << endl;
	}
};


class UnsharedConcreteFlyweight : public Flyweight
{
public:
	UnsharedConcreteFlyweight(const string& intrinsic_state) : Flyweight(intrinsic_state)
	{

	}
	~UnsharedConcreteFlyweight()
	{

	}

public:
	void Operation(const string& extrinsic_state)
	{
		cout << extrinsic_state << endl;
	}
};

class FlyweightFactory
{
private:
	vector<Flyweight*> _flyweight;
public:
	FlyweightFactory()
	{

	}
	~FlyweightFactory()
	{

	}

public:
	Flyweight* get_flyweight(const string& key)
	{
		vector<Flyweight*>::iterator iter = _flyweight.begin();
		for(; iter!=_flyweight.end(); ++iter)
		{
			if((*iter)->get_intrinsic_state() == key)
			{
				return *iter;
			}
		}
		return NULL;
	}

	int get_flyweight_count()
	{
		return _flyweight.size();
	}
};








#endif /* FLYWEIGHT_H_ */

/*
 * Mediator.h
 *
 *  Created on: May 5, 2014
 *      Author: Robert
 */

#ifndef MEDIATOR_H_
#define MEDIATOR_H_

#include <iostream>
using namespace std;


class Mediator;

class Person
{
protected:
	Mediator *_mediator;

public:
	Person() : _mediator(NULL)
	{
	}
	virtual ~Person()
	{

	}

public:
	void set_mediator(Mediator *mediator)
	{
		_mediator = mediator;
	}
	virtual void send_msg(const string& msg) = 0;
	virtual void get_msg(const string& msg) = 0;
};



class Mediator
{
private:
	Person* _personA;
	Person* _personB;

public:
	Mediator()
	{
		_personA = NULL;
		_personB = NULL;
	}
	virtual ~Mediator()
	{

	}

public:
	void set_a(Person* person)
	{
		_personA = person;
	}
	void set_b(Person* person)
	{
		_personB = person;
	}

	void send_msg(const string& msg, Person* send_person)
	{
		if(send_person == _personA)
		{
			_personB->get_msg(msg);
		}
		else
		{
			_personA->get_msg(msg);
		}
	}

};


class Render : public Person
{
public:
	Render()
	{

	}
	~Render()
	{

	}

public:
	void send_msg(const string& msg)
	{
		_mediator->send_msg(msg, this);
	}
	void get_msg(const string& msg)
	{
		cout << "Render get a msg" << endl;
	}
};

class Landlord : public Person
{
public:
	Landlord()
	{

	}
	~Landlord()
	{

	}
public:
	void send_msg(const string& msg)
	{
		_mediator->send_msg(msg, this);
	}
	void get_msg(const string& msg)
	{
		cout << "Landlord get a msg" << endl;
	}
};




void pattern_mediator_test()
{
	Mediator *mediaor = new Mediator();

	Render *one_render = new Render();
	Landlord *lord = new Landlord();

	one_render->set_mediator(mediaor);
	lord->set_mediator(mediaor);

	mediaor->set_a(one_render);
	mediaor->set_b(lord);

	one_render->send_msg("I want to rend a house");
	lord->send_msg("I have no house now");


	delete mediaor;
	delete one_render;
	delete lord;
}

#endif /* MEDIATOR_H_ */

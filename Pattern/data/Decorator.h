/*
 * Decorator.h
 *
 *  Created on: Apr 25, 2014
 *      Author: Robert
 */

#ifndef DECORATOR_H_
#define DECORATOR_H_

#include <cstdlib>
#include <iostream>

class Component
{
protected:
	Component() {}
public:
	virtual ~Component() {}

public:
	virtual void Operator() = 0;
};

class ConcreteComponent : public Component
{
public:
	ConcreteComponent() {}
	virtual ~ConcreteComponent() {}

	virtual void Operator() {}
};




class Decorator : public Component
{
protected:
	Component *_com;

public:
	Decorator(Component* com) { _com = com; }
	virtual ~Decorator() {}

public:
	void set_component(Component* com)
	{
		_com = com;
	}
	void Operator()
	{

	}
};

class ConcreteDecoratorA : public Decorator
{
public:
	ConcreteDecoratorA(Component* com) : Decorator(com)
	{

	}
	~ConcreteDecoratorA()
	{

	}

	void Operator()
	{
		this->_com->Operator();
		this->add_behavor_a();
	}

	void add_behavor_a()
	{
		std::cout << "附加功能A" << std::endl;
	}
};

class ConcreteDecoratorB : public Decorator
{
public:
	ConcreteDecoratorB(Component *com) : Decorator(com)
	{

	}
	~ConcreteDecoratorB()
	{

	}
	void Operator()
	{
		this->_com->Operator();
		this->add_behavor_b();
	}

	void add_behavor_b()
	{
		std::cout << "附加功能B" << std::endl;
	}
};


/*
 * 只添加一种装饰，不用抽象出装饰基类
 */
class DecoratorOnlyOne : public Component
{
private:
	Component *_com;
public:
	DecoratorOnlyOne(Component *com) { _com = com; }
	~DecoratorOnlyOne()
	{
		if(_com) delete _com;
	}

	void Operator()
	{
		_com->Operator();
		add_behavor();
	}

	void add_behavor()
	{
		std::cout << "附加功能" << std::endl;
	}
};

void pattern_decorator_test()
{
	Component* com = new ConcreteComponent();

	Decorator* dec = new ConcreteDecoratorA(com);
	dec = new ConcreteDecoratorB(com);

	dec->Operator();
	delete com;
}

#endif /* DECORATOR_H_ */

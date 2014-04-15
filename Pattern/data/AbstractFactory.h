/*
 * AbstractFactory.h
 *
 *  Created on: Apr 15, 2014
 *      Author: Robert
 */

#ifndef ABSTRACTFACTORY_H_
#define ABSTRACTFACTORY_H_

class ProductA
{
public:
	virtual ~ProductA() {}
	virtual void show() = 0;
};

class ProductA1 : public ProductA
{
public:
	void show() {}
};

class ProductA2 : public ProductA
{
public:
	void show() {}
};

class ProductB
{
public:
	virtual ~ProductB() {}
	virtual void show() = 0;
};

class ProductB1 : public ProductB
{
public:
	void show() {}
};

class ProductB2 : public ProductB
{
public:
	void show() {}
};




class AbstractFactory
{
public:
	AbstractFactory();
	virtual ~AbstractFactory();

public:
	virtual ProductA* create_product_a() = 0;
	virtual ProductB* create_product_b() = 0;
};


class Factory1 : public AbstractFactory
{
public:
	ProductA* create_product_a()
	{
		return new ProductA1();
	}
	ProductB* create_product_b()
	{
		return new ProductB1();
	}
};

class Factory2 : public AbstractFactory
{
public:
	ProductA* create_product_a()
	{
		return new ProductA2();
	}
	ProductB* create_product_b()
	{
		return new ProductB2();
	}
};


#endif /* ABSTRACTFACTORY_H_ */

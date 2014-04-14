/*
 * SimpleFactory.h
 *
 *  Created on: Apr 14, 2014
 *      Author: Robert
 */

#ifndef SIMPLEFACTORY_H_
#define SIMPLEFACTORY_H_

#include <cstdlib>
#include <iostream>

class Product
{
public:
	Product() {}
	virtual ~Product() {}

public:
	virtual void show() = 0;
};

class ProductA : public Product
{
public:
	ProductA() {}
	virtual ~ProductA() {}

public:
	virtual void show() {};
};


class ProductB : public Product
{
public:
	ProductB() {}
	virtual ~ProductB() {}

public:
	virtual void show() {};
};


class SimpleFactory
{
public:
	SimpleFactory();
	virtual ~SimpleFactory();

public:
	static Product* create_product(const std::string &name);
};

#endif /* SIMPLEFACTORY_H_ */

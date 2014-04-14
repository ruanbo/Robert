/*
 * FactoryMethod.h
 *
 *  Created on: Apr 14, 2014
 *      Author: Robert
 */

#ifndef FACTORYMETHOD_H_
#define FACTORYMETHOD_H_

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
	~ProductA() {}

public:
	void show() {}
};

class ProductB : public Product
{
public:
	ProductB() {}
	~ProductB() {}

public:
	void show() {}
};

//////////////

class FactoryMethod
{
public:
	FactoryMethod();
	virtual ~FactoryMethod();

public:
	virtual Product* create_product() = 0;
};


class AFactory : public FactoryMethod
{
public:
	AFactory() {}
	~AFactory() {}

public:
	ProductA* create_product() { return new ProductA; }
};


class BFactory : public FactoryMethod
{
public:
	BFactory() {}
	~BFactory() {}

public:
	ProductB* create_product() { return new ProductB; }
};

#endif /* FACTORYMETHOD_H_ */

/*
 * SimpleFactory.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: Robert
 */

#include "SimpleFactory.h"

SimpleFactory::SimpleFactory()
{

}

SimpleFactory::~SimpleFactory()
{

}


Product* SimpleFactory::create_product(const std::string &name)
{
	if(name == "A")
	{
		return new ProductA();
	}
	else if(name == "B")
	{
		return new ProductB();
	}
	else
	{
		std::cout << "do not have this kind of product" << std::endl;
	}

	return NULL;
}

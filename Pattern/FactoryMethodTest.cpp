/*
 * FactoryMethodTest.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: Robert
 */


#include "Define.h"

#include "data/FactoryMethod.h"

void factory_method_test()
{
	AFactory* a_factory = new AFactory();

	ProductA* product_a = a_factory->create_product();

	delete a_factory;
	delete product_a;
}



/*
 * SingletonTest.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: Robert
 */



#include "Define.h"
#include "data/Singleton.h"



void singleton_test()
{
	Singleton0 * inst0 = Singleton0::get_instance();
	inst0->show();

	Singleton1 * inst1 = Singleton1::get_instance();
	inst1->show();
	delete inst1;

	Singleton2 * inst2 = Singleton2::get_instance();
	inst2->show();
	delete inst2;

	Singleton3 * inst3 = Singleton3::get_instance();
	inst3->show();

	Singleton4 * inst4 = Singleton4::get_instance();
	inst4->show();

//	delete inst1;
}

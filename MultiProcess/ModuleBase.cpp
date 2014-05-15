/*
 * ModuleBase.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Robert
 */

#include "ModuleBase.h"

ModuleBase::ModuleBase(const std::string& tag)
{
	_tag = tag;
	_host = "";
	_port = 0;
}

ModuleBase::~ModuleBase()
{

}


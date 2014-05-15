/*
 * ModuleBase.h
 *
 *  Created on: May 13, 2014
 *      Author: Robert
 */

#ifndef MODULEBASE_H_
#define MODULEBASE_H_

#include <string>

class ModuleBase
{
private:
	std::string _tag;
	std::string _host;
	int _port;


public:
	ModuleBase(const std::string& tag);

	virtual ~ModuleBase();

public:
	std::string get_tag()const;
};

#endif /* MODULEBASE_H_ */

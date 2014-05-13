/*
 * RobertMySql.cpp
 *
 *  Created on: May 9, 2014
 *      Author: Robert
 */

#include "RobertMySql.h"

#include <iostream>
using namespace std;

static string SQL_CREATE_DB = "Create Database If Not Exists ";
static string SQL_CREATE_TB = "Create Table If Not Exists players(id INT(11), name VARCHAR(20), sex TINYINT(2), career TINYINT(2), lvl TINYINT(2))";


RobertMySql::RobertMySql()
{
	_mysql = NULL;
}

RobertMySql::~RobertMySql()
{

}

bool RobertMySql::init()
{
	_mysql = mysql_init(NULL);

	if(_mysql == NULL)
	{
		return false;
	}
	return true;
}

bool RobertMySql::uninit()
{
	mysql_close(_mysql);

	return true;
}

void RobertMySql::close_when_error()
{
	cout << mysql_errno(_mysql) << endl;
	mysql_close(_mysql);
}

bool RobertMySql::conn_db(const std::string& host, int port, const std::string& db_name, const std::string& user, const std::string& password)
{
	if(!mysql_real_connect(_mysql, host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), port, NULL, 0))
	{
		close_when_error();
		return false;
	}
	return true;
}

bool RobertMySql::create_db(const std::string& db_name)
{
	string create_sql = SQL_CREATE_DB + db_name;

	int ret = mysql_real_query(_mysql, create_sql.c_str(), create_sql.size());
	if(ret != 0)
	{
		close_when_error();
		return false;
	}

	return true;
}

bool RobertMySql::crate_tb(const std::string& tb_name)
{
	int ret = mysql_real_query(_mysql, SQL_CREATE_TB.c_str(), SQL_CREATE_TB.size());
	if(ret != 0)
	{
		close_when_error();
		return false;
	}
	return true;
}

void RobertMySql::find_data()const
{
//	MYSQL_RES * res;

}


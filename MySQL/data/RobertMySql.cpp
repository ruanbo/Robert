/*
 * RobertMySql.cpp
 *
 *  Created on: May 9, 2014
 *      Author: Robert
 */

#include "RobertMySql.h"

using namespace std;

static string SQL_CREATE_DB = "Create Database If Not Exists ";
//static string SQL_CREATE_TB = "Create Table If Not Exists";

RobertMySql::RobertMySql()
{
	_mysql = NULL;
}

RobertMySql::~RobertMySql()
{
	// TODO Auto-generated destructor stub
}

bool RobertMySql::init()
{
	_mysql = mysql_init(_mysql);

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

bool RobertMySql::conn_db(const std::string& host, int port, const std::string& db_name, const std::string& user, const std::string& password)
{
	if(!mysql_real_connect(_mysql, host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), port, NULL, 0))
	{
		cout << "mysql_real_connect() error:" << mysql_error(_mysql) << endl;
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
		cout << "mysql_real_query() error:" << mysql_error(_mysql) << endl;
		return false;
	}

	return true;
}

bool RobertMySql::crate_tb(const std::string& tb_name)
{
	return true;
}


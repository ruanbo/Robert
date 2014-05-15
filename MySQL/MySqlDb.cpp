/*
 * MySqlDb.cpp
 *
 *  Created on: May 9, 2014
 *      Author: Robert
 */


#include "MySQL/MySqlHeader.h"
#include "data/RobertMySql.h"



void mysql_first_test()
{
//	mysql_library_init();

	MYSQL* mysql = NULL;
	mysql = mysql_init(NULL);

	mysql = mysql_real_connect(mysql, "127.0.0.1", "root", "123456", "test", 3306, NULL, 0);

	if(mysql == NULL)
	{
		cout << "mysql_real_connect() error:" << mysql_error(mysql) << endl;
		exit(0);
	}

	string create_tb = "Create Table If Not Exists tb_name(id INT(11))";
	if(mysql_real_query(mysql, create_tb.c_str(), create_tb.size()) != 0)
	{
		cout << "mysql_real_query() error:" << mysql_error(mysql) << endl;
		exit(0);
	}

//	mysql_real_query(mysql, "create table if not ")

	mysql_close(mysql);
	mysql_library_end();

	cout << "end of mysql_first_test()" << endl;
}



void mysql_test()
{
	RobertMySql *rb_sql = new RobertMySql();

	if(rb_sql->init() == false)
	{
		exit(0);
	}

	if( rb_sql->conn_db("127.0.0.1", 3306, "test", "root", "123456") == false)
	{
		exit(0);
	}

	if( rb_sql->crate_tb() == false)
	{
		exit(0);
	}


	delete rb_sql;
}



/*
 * MySqlDb.cpp
 *
 *  Created on: May 9, 2014
 *      Author: Robert
 */


#include "MySQL/MySqlHeader.h"


string create_tb = "Create Table If Not Exists tb_name(id INT(11))";




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



/*
 * DBCompare.cpp
 *
 *  Created on: May 14, 2014
 *      Author: Robert
 */

#include "MySQL/MySqlHeader.h"
#include <boost/format.hpp>

string create_tb_players = "Create Table If Not Exists players(id INT(11) Unique, name VARCHAR(20), career TINYINT(2), gender TINYINT(2), nation TINYINT(2))";

string tb_insert_players = "Insert Into players Values(%d, '%s', 1, 1, 2)";

string tb_find_player = "Select 1 From players Where id=%d Limit 1";


void mysql_insert_test(MYSQL *sql_inst)
{
	int ret = mysql_real_query(sql_inst, create_tb_players.c_str(), create_tb_players.length());
	if(ret != 0)
	{
		cout << mysql_error(sql_inst) << endl;
	}

	DeltaTime delta_time("(MySQL) insert 100000 record");

	for(int i=1; i<100000; ++i)
	{
		string insert_str = (boost::format(tb_insert_players.c_str()) % i % "robert").str();
		ret = mysql_real_query(sql_inst, insert_str.c_str(), insert_str.length());
		if(ret != 0)
		{
			cout << "mysql_real_query() error:" << mysql_error(sql_inst) << endl;
		}
	}
}

void mysql_find_test(MYSQL *sql_inst)
{
	string find_str = (boost::format(tb_find_player) % 1000).str();
	DeltaTime delta_time("(MySQL) find 10000 record");

	for(int i=0; i<10000; ++i)
	{
		int ret = mysql_real_query(sql_inst, find_str.c_str(), find_str.length());
		if(ret != 0)
		{
			cout << "mysql_real_query() error:" << mysql_error(sql_inst) << endl;
			return;
		}

		MYSQL_RES *result = mysql_store_result(sql_inst);
		mysql_free_result(result);
	}
}


void mysql_cmp_test()
{
	MYSQL *sql_inst = NULL;
	sql_inst = mysql_init(NULL);
	if(sql_inst == NULL)
	{
		cout << "mysql_init() error:" << mysql_error(sql_inst) << endl;
		exit(0);
	}

	sql_inst = mysql_real_connect(sql_inst, "127.0.0.1", "root", "123456", "test", 3306, NULL, 0);
	if(sql_inst == NULL)
	{
		cout << "mysql_real_connect() error:" << mysql_error(sql_inst) << endl;
		exit(0);
	}

	{
		mysql_find_test(sql_inst);

//		mysql_insert_test(sql_inst);
	}

	mysql_close(sql_inst);
	mysql_library_end();
}



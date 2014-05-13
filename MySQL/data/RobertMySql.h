/*
 * RobertMySql.h
 *
 *  Created on: May 9, 2014
 *      Author: Robert
 */

#ifndef ROBERTMYSQL_H_
#define ROBERTMYSQL_H_

#include <string>

#include <mysql/mysql.h>



class RobertMySql
{
private:
	MYSQL* _mysql;
public:
	RobertMySql();
	virtual ~RobertMySql();

public:
	bool init();

	bool uninit();

	void close_when_error();

	bool conn_db(const std::string& host, int port, const std::string& db_name, const std::string& user, const std::string& password);

	bool create_db(const std::string& db_name);

	bool crate_tb(const std::string& tb_name="test");

	void find_data()const;


};

#endif /* ROBERTMYSQL_H_ */

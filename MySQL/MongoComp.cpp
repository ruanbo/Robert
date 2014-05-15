/*
 * MongoComp.cpp
 *
 *  Created on: May 14, 2014
 *      Author: Robert
 */


#include "MySqlHeader.h"
#include "mongo/client/dbclient.h"

using namespace mongo;

void mongo_insert_test()
{
	mongo::BSONObjBuilder b;
	b.append("_id", 1);
	b.append("name", "Robert");
	b.append("career", 1);
	b.append("gender", 1);
	b.append("nation", 1);

	BSONObj p = b.obj();

}


void mongo_conn_test(DBClientConnection *db_conn)
{

	int64_t begin_us = get_now_us();

	for(int i=1; i<100000; ++i)
	{
		mongo::BSONObjBuilder b;
		b.append("_id", i);
		b.append("name", "Robert");
		b.append("career", 1);
		b.append("gender", 1);
		b.append("nation", 1);

		BSONObj p = b.obj();

		db_conn->insert("tb_test.players", p);
	}

	int64_t end_us = get_now_us();

	cout << "(Mongo)insert 100000 record time(us):" << (end_us - begin_us) << endl;
}

void mongo_remove_test(DBClientConnection *db_conn, int pid)
{
	{
		mongo::BSONObjBuilder b;
		b.append("_id", 1);

		db_conn->remove("tb_test.players", Query(b.obj()));
	}
}

void mongo_find_test(DBClientConnection *db_conn)
{
	DeltaTime rcd_time("(Mongo)find 1000 record");

	for(int i=0; i<10000; ++i)
	{
		BSONObjBuilder b;
		b.append("_id", 1000);

		db_conn->findOne("tb_test.players", Query(b.obj()));
	}
}


void mongo_cmp_test()
{
	try {
		mongo::DBClientConnection *db_conn = new DBClientConnection();

		db_conn->connect("127.0.0.1:27017");

//		mongo_conn_test(db_conn);

//		mongo_remove_test(db_conn, 1);

		mongo_find_test(db_conn);

		delete db_conn;
	}
	catch (DBException& e) {
		cout << "error:" << e.what() << endl;
	}
}






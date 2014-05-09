/*
 * main.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: root
 */


#include "Define.h"

#include "Func.h"

void test_func()
{
	string msg;
	u_int64_t num = 0;


	u_int16_t packet_type = 1;
	u_int16_t packet_size = 12;

	cout << "sizeof(packet_type):" << sizeof(packet_type) << endl;

	{
		num++;
		msg.append((char*)&packet_type, sizeof(packet_size));
		msg.append((char*)&packet_size, sizeof(packet_type));
		msg.append((char*)&num, sizeof(num));

		cout << "msg.len:" << msg.length() << endl;
		cout << "msg.size:" << msg.size() << endl;
	}

	{
		num++;
		msg.append((char*)&packet_type, sizeof(packet_size));
		msg.append((char*)&packet_size, sizeof(packet_type));
		msg.append((char*)&num, sizeof(num));
	}



	u_int16_t type = 0;
	u_int16_t size = 0;
	u_int64_t recv_num = 0;

	{
		msg.copy((char*)&type, sizeof(type), 0);
		msg.copy((char*)&size, sizeof(size), 2);
		msg.copy((char*)&recv_num, sizeof(recv_num), 4);

		cout << "type:" << type << endl;
		cout << "size:" << size << endl;
		cout << "recv_num:" << recv_num << endl;
	}

	msg.erase(0, 12);

	{
		msg.copy((char*)&type, sizeof(type), 0);
		msg.copy((char*)&size, sizeof(size), 2);
		msg.copy((char*)&recv_num, sizeof(recv_num), 4);

		cout << "type:" << type << endl;
		cout << "size:" << size << endl;
		cout << "recv_num:" << recv_num << endl;
	}

	char read_buf[1024];
	bzero(read_buf, sizeof(read_buf));

	cout << "sizeof(read_buf):" << sizeof(read_buf) << endl;
	cout << "strlen(read_buf):" << strlen(read_buf) << endl;

}



int main()
{
//	debug_info("boost version: %d", BOOST_VERSION);

//	test_func();

	all_test_func_entry();


//	string str;
//
//	while(true)
//	{
//		cin >> str;
//
//		cout << "buf:" << str << endl;
//
//		if(str == "quie")
//		{
//			break;
//		}
//	}

	cout << endl << "end of main" << endl << endl;

	return 0;
}

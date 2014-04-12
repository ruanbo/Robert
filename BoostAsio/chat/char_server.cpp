///*
// * char_server.cpp
// *
// *  Created on: Mar 14, 2014
// *      Author: root
// */
//
//#include "Define.h"
//#include "chat_message.hpp"
//
//#include <algorithm>
//#include <boost/bind.hpp>
//#include <boost/enable_shared_from_this.hpp>
//#include <boost/asio.hpp>
//
//
//using boost::asio::ip::tcp;
//
//typedef std::deque<chat_message> chat_message_queue;
//
//class chat_participant
//{
//public:
//	virtual ~chat_participant() {}
//	virtual void deliver(const chat_message& msg) = 0;
//};
//
//typedef boost::shared_ptr<chat_participant> chat_participant_ptr;
//
//
//
//class chat_room
//{
//private:
//	std::set<chat_participant_ptr> _participants;
//	enum { max_recent_msgs = 100 };
//	chat_message_queue _recent_msgs;
//
//public:
//	void join(chat_participant_ptr participant)
//	{
//		_participants.insert(participant);
//		std::for_each(_recent_msgs.begin(), _recent_msgs.end(),
//			boost::bind(&chat_participant::deliver, participant, _1));
//	}
//
//	void leave(chat_participant_ptr participant)
//	{
//		_participants.erase(participant);
//	}
//
//	void deliver(const chat_message& msg)
//	{
//		_recent_msgs.push_back(msg);
//		while(_recent_msgs.size() > max_recent_msgs)
//		{
//			_recent_msgs.pop_front();
//		}
//
//		std::for_each(_participants.begin(), _participants.end(),
//			boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
//	}
//};
//
//
//
//class chat_session : public chat_participant, public boost::enable_shared_from_this<chat_session>
//{
//private:
//	tcp::socket _socket;
//	chat_room& _room;
//	chat_message _read_msg;
//	chat_message_queue _write_msgs;
//
//public:
//	chat_session(boost::asio::io_service& io_server, chat_room& room)
//		: _socket(io_server), _room(room)
//	{
//
//	}
//
//	tcp::socket& socket()
//	{
//		return _socket;
//	}
//
//	void start()
//	{
//
//	}
//
//	void deliver(const chat_message& msg)
//	{
//
//	}
//
//	void handle_read_header(const boost::system::error_code& error)
//	{
//
//	}
//
//	void handle_read_body(const boost::system::error_code& error)
//	{
//
//	}
//
//	void handler_write(const boost::system::error_code& error)
//	{
//
//	}
//};
//
//typedef boost::shared_ptr<chat_session> chat_session_ptr;
//
//
//
//class chat_server
//{
//private:
//	boost::asio::io_service& _io_server;
//	tcp::acceptor _acceptor;
//	chat_room _room;
//
//public:
//	chat_server(boost::asio::io_service& io_server,
//		const tcp::endpoint& endpoint)
//	   : _io_server(io_server), _acceptor(io_server, endpoint)
//	{
//		chat_session_ptr new_session(new chat_session(_io_server, _room));
//		_acceptor.async_accept(new_session->socket(),
//			boost::bind(&chat_server::handle_accept, this, new_session, boost::asio::placeholders::error));
//	}
//
//	void handle_accept(chat_session_ptr session, boost::system::error_code& error)
//	{
//		if(!error)
//		{
//			session->start();
//
//			chat_session_ptr new_session(new chat_session(_io_server, _room));
//
//			_acceptor.async_accept(new_session->socket(),
//				boost::bind(&chat_server::handle_accept, this, new_session,
//					boost::asio::placeholders::error));
//		}
//	}
//};
//
//typedef boost::shared_ptr<chat_server> chat_server_ptr;
//
//typedef std::list<chat_server_ptr> chat_server_list;
//
//
//
//int chat_server_test()
//{
//	try
//	{
//		boost::asio::io_service io_server;
//		chat_server_list servers;
//
//		tcp::endpoint end_point(tcp::v4(), 10086);
//		chat_server_ptr one_server(new chat_server(io_server, end_point));
//
//		servers.push_back(one_server);
//
//		io_server.run();
//	}
//	catch(std::exception& ex)
//	{
//		cout << "exception happened: " << ex.what() << endl;
//	}
//
//	return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//

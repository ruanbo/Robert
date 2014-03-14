/*
 * TcpServerTest.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: root
 */

#include "Define.h"

#include <ctime>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

string make_daytime_string()
{
	time_t now = time(0);

	return ctime(&now);
}



void tcp_server_test1()
{
	try
	{
		boost::asio::io_service io_server;

		tcp::acceptor acceptor(io_server, tcp::endpoint(tcp::v4(), 1300));

		for (;;)
		{
			tcp::socket socket(io_server);

			acceptor.accept(socket);

			string msg = make_daytime_string();

			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(msg),
					boost::asio::transfer_all(), ignored_error);
		}
	}
	catch(std::exception &e)
	{
		cout << "exception happened:" << e.what() << endl;
	}

	return;
}

// async_tcp_server

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
private:
	tcp::socket _socket;
	string _message;

public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_service& io_server)
	{
		return pointer(new tcp_connection(io_server));
	}

	tcp::socket& socket()
	{
		return _socket;
	}

	void start()
	{
		_message = make_daytime_string();

		boost::asio::async_write(_socket, boost::asio::buffer(_message),
				boost::bind(&tcp_connection::handle_write, shared_from_this(),
					boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

private:
	tcp_connection(boost::asio::io_service& io_server) : _socket(io_server)
	{

	}

	void handle_write(const boost::system::error_code&, size_t)
	{

	}
};


class tcp_server
{
private:
	tcp::acceptor _acceptor;

public:
	tcp_server(boost::asio::io_service& io_server) :
		_acceptor(io_server, tcp::endpoint(tcp::v4(), 1300))
	{

	}

private:
	void start_accept()
	{
		tcp_connection::pointer new_connection = tcp_connection::create(_acceptor.io_service());

		_acceptor.async_accept(new_connection->socket(),
				boost::bind(&tcp_server::handle_accept, this, new_connection, boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection,
			const boost::system::error_code& error)
	{
		if(!error)
		{
			new_connection->start();
			start_accept();
		}
	}
};

void async_tcp_server_test()
{
	try
	{
		boost::asio::io_service io_server;

		tcp_server server(io_server);

		io_server.run();
	}
	catch(exception& ex)
	{
		cout << "exception happened:" << ex.what() << endl;
	}
}















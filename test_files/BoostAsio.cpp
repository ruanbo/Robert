/*
 * BoostAsio.cpp
 *
 *  Created on: Jan 13, 2014
 *      Author: root
 */


#include "Define.h"

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;


void some_asio_funcs()
{
	boost::asio::io_service my_io_server;

	boost::asio::ip::tcp::socket socket(my_io_server);
}

/*
 * 同步定时器， 阻塞等待
 */
void asio_sync_timer()
{
	boost::asio::io_service my_io;

	int32 wait_sec = 5;

	boost::asio::deadline_timer t(my_io, boost::posix_time::seconds(wait_sec));

	t.wait();

	debug_info("after %d seconds. hello world !", wait_sec);
}


/*
 * 异步定时器, 非阻塞等待
 */
void async_print(const boost::system::error_code&)
{
	debug_info("end of asio_async_timer");
}

void asio_async_timer()
{
	boost::asio::io_service my_io;

	boost::asio::deadline_timer t(my_io, boost::posix_time::seconds(5));

	t.async_wait(async_print);

	my_io.run();
}


void async_print2(const boost::system::error_code&, boost::asio::deadline_timer* t, int* count)
{
	if(*count < 5)
	{
		++(*count);
		debug_info("count: %d \n", *count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(async_print2, boost::asio::placeholders::error, t, count));
	}
}

void boost_async_timer2()
{
	boost::asio::io_service my_io;

	int count = 0;

	boost::asio::deadline_timer t(my_io, boost::posix_time::seconds(1));

	t.async_wait(boost::bind(async_print2, boost::asio::placeholders::error, &t, &count));

	my_io.run();

	debug_info("final count: %d", count);
}


class async_printer
{
private:
	boost::asio::deadline_timer _timer;
	int32 _count;

public:
	async_printer(boost::asio::io_service& io) : _timer(io, boost::posix_time::seconds(1)), _count(0)
	{
		_timer.async_wait(boost::bind(&async_printer::print, this));
	}

	~async_printer()
	{
		debug_info("final count: %d \n", _count);
	}

public:
	void print()
	{
		if(_count < 5)
		{
			debug_info("count: %d \n", ++_count);

			_timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));

			_timer.async_wait(boost::bind(&async_printer::print, this));
		}
	}
};

void boost_async_timer_class_func()
{
	boost::asio::io_service my_io;

	async_printer printer(my_io);

	my_io.run();
}

void boost_asio_test()
{
//	asio_sync_timer();

//	asio_async_timer();

//	boost_async_timer2();

	boost_async_timer_class_func();

}


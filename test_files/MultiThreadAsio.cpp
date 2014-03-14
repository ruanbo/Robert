/*
 * MultiThreadAsio.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: root
 */


#include "Define.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


class printer
{
private:
	boost::asio::strand _strand;
	boost::asio::deadline_timer _timer1;
	boost::asio::deadline_timer _timer2;
	int32 _count;

public:
	printer(boost::asio::io_service& io)
		:_strand(io),_timer1(io, boost::posix_time::seconds(1)), _timer2(io, boost::posix_time::seconds(1)), _count(0)
	{
		_timer1.async_wait(_strand.wrap(boost::bind(&printer::print1, this)));
		_timer2.async_wait(_strand.wrap(boost::bind(&printer::print2, this)));
	}

	~printer()
	{

	}

public:
	void print1()
	{
		if(_count < 10)
		{
			_count++;

			debug_info("print1,count: %d", _count);

			_timer1.expires_at(_timer1.expires_at() + boost::posix_time::seconds(1));
			_timer1.async_wait(_strand.wrap(boost::bind(&printer::print1, this)));
		}
	}

	void print2()
	{
		if(_count < 10)
		{
			_count++;

			debug_info("print2,count: %d", _count);

			_timer2.expires_at(_timer2.expires_at() + boost::posix_time::seconds(1));
			_timer2.async_wait(_strand.wrap(boost::bind(&printer::print2, this)));
		}
	}

};

void thread_asio_test_1()
{
	boost::asio::io_service my_io;

	printer my_printer(my_io);

	boost::thread t(boost::bind(&boost::asio::io_service::run, &my_io));

	my_io.run();
	t.join();

}

void multi_thread_asio_test()
{
	thread_asio_test_1();
}


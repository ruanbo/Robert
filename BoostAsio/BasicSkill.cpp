
#include "Define.h"

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>


void sync_timer()
{
	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

	t.wait();

	cout << "end of sync_timer()" << endl;
}


void async_callback(const boost::system::error_code & ec)
{
	cout << "async call back" << endl;
}

void async_timer()
{
	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

	t.async_wait(async_callback);

	io.run();
}



//
void print(const boost::system::error_code&, boost::asio::deadline_timer* t, int *count)
{
	if(*count < 5)
	{
		cout << *count << endl;
		++(*count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
	}
}

void bind_wait()
{
	boost::asio::io_service io;

	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
	t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));

	io.run();

	cout << "final count: " << count << endl;
}









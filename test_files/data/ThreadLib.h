/*
 * ThreadLib.h
 *
 *  Created on: Apr 9, 2014
 *      Author: root
 */

#ifndef THREADLIB_H_
#define THREADLIB_H_

#include "Define.h"

class Exception : public exception
{
private:
	string _msg;

public:
	explicit Exception(const string & msg = "")
	{
		_msg = msg;
	}
	virtual ~Exception() throw()
	{

	}
	virtual const char *what() const throw()
	{
		return _msg.c_str();
	}
};

class ThreadException : public Exception
{
public:
	ThreadException(const string & msg = "") : Exception(msg)
	{

	}
};

class ThreadCreateException : public Exception
{
public:
	ThreadCreateException(const string & msg = "") : Exception(msg)
	{

	}
};

class ThreadLib;


class ThreadImpl
{
private:
	ThreadImpl();
	ThreadImpl(const ThreadImpl &)throw();
	void operator=(const ThreadImpl&);

public:
	static const int WAIT_INFINITE = -1;
	static const int INVALID_THREAD_ID = 0;
	static const size_t DEFAULT_STACK_SIZE = 0;
	static const int WAIT_TIME_SLICE = 10;

public:
	typedef int (*THREAD_FUNCTION)(ThreadLib *thread);
	typedef void *(*THREAD_ROUTINE)(void *params);

	typedef boost::function<void* (void *)> Thread_Routine;
	typedef boost::function<int (void *)> Thread_Function;

public:
	struct ThreadStruct {
		pthread_t _thread_id;

		ThreadStruct() : _thread_id(INVALID_THREAD_ID)
		{
		}

		~ThreadStruct()
		{

		}
	};

	static bool create_thread(ThreadStruct &ts, THREAD_FUNCTION thread_func,
							size_t stack_size, ThreadLib *thread)
	{
		pthread_attr_t *p_attr = NULL;
		pthread_attr_t attr;

		if(stack_size != DEFAULT_STACK_SIZE)
		{
			if(pthread_attr_init(&attr) != 0)
			{
				return false;
			}
			if(pthread_attr_setstacksize(&attr, stack_size) != 0)
			{
				pthread_attr_destroy(&attr);
				return false;
			}
			p_attr = &attr;
		}

		int ret = pthread_create(&(ts._thread_id), p_attr,
								(THREAD_ROUTINE)thread_func, (void*)thread);
		if(p_attr != NULL)
		{
			pthread_attr_destroy(&attr);
		}
		if(ret != 0)
		{
			return false;
		}

		pthread_detach(ts._thread_id);

		return true;
	}

	static void destory_thread(ThreadStruct & ts)
	{
		pthread_exit(NULL);
	}

	static bool wait_for_thread_end(const ThreadStruct & ts, int32 time_out)
	{
		int32 delta = WAIT_TIME_SLICE;
		int total = time_out;

		if(time_out == WAIT_INFINITE)
		{
			delta = 0;
			total = 1;
		}

		for(int i=0; i<total; i+=delta)
		{
			if(is_alive(ts) == false)
			{
				return true;
			}
			else
			{
				imp_sleep(WAIT_TIME_SLICE);
			}
		}
		return false;
	}

	static void termanite_thread(ThreadStruct & ts)
	{
		pthread_cancel(ts._thread_id);
	}

	static bool is_alive(const ThreadStruct & ts)
	{
		int policy;
		struct sched_param sp;

		int ret = pthread_getschedparam(ts._thread_id, &policy, &sp);

		if(ret == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static int get_thread_id(const ThreadStruct & ts)
	{
		return (int)ts._thread_id;
	}

	static void imp_sleep(int ms)
	{
		int sleep_s = ms / 1000;
		int sleep_us = (ms % 1000) * 1000;

		if(sleep_s > 0)
		{
			sleep(sleep_s);
		}

		if(sleep_us > 0)
		{
			usleep(sleep_us);
		}
	}
};


//class ThreadImpl;

class ThreadLib
{
protected:
	string _thread_name;
	ThreadImpl::ThreadStruct _ts;

public:
	static const int WAIT_INFINITE = ThreadImpl::WAIT_INFINITE;
	static const int INVALID_THREAD_ID = ThreadImpl::INVALID_THREAD_ID;
	static const size_t DEFAULT_STACK_SIZE = ThreadImpl::DEFAULT_STACK_SIZE;


public:
	explicit ThreadLib(const string & thread_name="")
	{
		_thread_name = thread_name;
	}

	virtual ~ThreadLib()
	{
		if(is_alive())
		{
			on_leaking();
		}
	}

private:
	ThreadLib(const ThreadLib &)throw();
	void operator = (const ThreadLib&);

private:
	virtual void run() {}

	virtual void on_exception(const Exception *ex){}

	virtual void on_leaking() throw(){}

	static int thread_func(ThreadLib *thread)
	{
		try
		{
			thread->run();
		}
		catch (const Exception & ex)
		{
			thread->on_exception(&ex);
			return -1;
		}
		catch(...)
		{
			thread->on_exception(NULL);
			return -1;
		}
		return 0;
	}

public:
	virtual void start(size_t stack_size=DEFAULT_STACK_SIZE)
	{
		bool ret = ThreadImpl::create_thread(_ts, thread_func, stack_size, static_cast<ThreadLib*>(this));
		if(ret == false)
		{
			throw ThreadCreateException("call ThreadImp::create_thread failed");
		}
	}

	bool wait_for_end(int timeout_ms=WAIT_INFINITE)
	{
		if(ThreadImpl::is_alive(_ts) == false)
		{
			return true;
		}

		if(ThreadImpl::wait_for_thread_end(_ts, timeout_ms) == false)
		{
			return false;
		}

		ThreadImpl::destory_thread(_ts);
		return true;
	}

	virtual void terminate()
	{
		ThreadImpl::termanite_thread(_ts);
		ThreadImpl::destory_thread(_ts);
	}

	virtual bool is_alive()
	{
		return ThreadImpl::is_alive(_ts);
	}

	string get_name()const
	{
		return _thread_name;
	}
	void set_thread_name(const string & name)
	{
		_thread_name = name;
	}

	uint32 get_id()const
	{
		return ThreadImpl::get_thread_id(_ts);
	}

	static void sleep(int32 ms)
	{
		return ThreadImpl::imp_sleep(ms);
	}

};











#endif /* THREADLIB_H_ */

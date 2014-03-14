/*
 * TempTimer.cpp
 *
 *  Created on: Mar 12, 2014
 *      Author: root
 */


#include "Define.h"

#include <ctime>


#define TIMER_DELAY_100MS 1000


class TempTimer : public smart_count
{
public:
	typedef boost::function<void()> TimerCallback;

private:
	int64 _when;
	int64 _interval;

	TimerCallback _cb;
	bool _repeat;

public:
	TempTimer(const TimerCallback cb, int64 when, int64 interval=0)
	{
		_when = when;
		_interval = interval;

		_cb = cb;
		_repeat = (interval>0);
	}

	virtual ~TempTimer()
	{

	}

public:
	void run()const
	{
		_cb();
	}

	bool repeat()const
	{
		return _repeat;
	}

	int64 when()const
	{
		return _when;
	}

	void update(int64 when)
	{
		_when = when;
	}
	int64 interval()const
	{
		return _interval;
	}
};
typedef smart_ptr<TempTimer> TempTimerPtr;

struct DetialTime
{
	int32 _now_sec;	//时间戳秒
	int32 _year;	//年 如 2012
	int32 _mon;		//月	 1～12
	int32 _day;		//日  1～31
	int32 _hour;	//时	 0～23
	int32 _min;		//分 0～59
	int32 _sec;		//秒 0～59

	int32 _wday;	//星期几 0是星期天

	DetialTime()
	{
		_now_sec = 0;
		_year = 0;
		_mon = 0;
		_day = 0;
		_hour = 0;
		_min = 0;
		_sec = 0;

		_wday = 0;
	}

	DetialTime(int32 now_seconds)
	{
		time_t now = now_seconds;
		struct tm store;
		struct tm* t = localtime_r(&now, &store);

		_now_sec = now_seconds;
		_year = 1900 + t->tm_year;	//年 如 2012
		_mon = 1 + t->tm_mon;		//月	 1～12
		_day = t->tm_mday;		//日  1～31
		_hour = t->tm_hour;	//时	 0～23
		_min = t->tm_min;		//分 0～59
		_sec = t->tm_sec;		//秒 0～59

		_wday = t->tm_wday;
	}

	virtual ~DetialTime()
	{

	}
};

class ModuleTimerManager
{
private:
	list<TempTimerPtr> _timer_queue;
	int64 _now_ms;

public:
	ModuleTimerManager()
	{
		_now_ms = 0;
	}

	virtual ~ModuleTimerManager()
	{

	}

public:
	void add_timer(const TempTimerPtr & timer)
	{
		_timer_queue.push_back(timer);
	}

	void update_time(int64 ms)
	{
		_now_ms = ms;
	}

	void run()
	{
		foreach_iterator(iter, _timer_queue.begin(), _timer_queue.end())
		{
			TempTimerPtr one_timer = *iter;
			if(one_timer->when() > _now_ms)
			{
				continue;
			}

			one_timer->run();
			one_timer->update(_now_ms+one_timer->interval());
		}
	}
};

class TimerModule
{
private:
	DetialTime _now_time;
	int64 _now_ms;
	int32 _now_sec;

	ModuleTimerManager _timer_manager;

public:
	TimerModule()
	{
		_now_ms = 0;
		_now_sec = 0;
	}

	virtual ~TimerModule()
	{

	}

public:
	void on_timer_100ms()
	{
		DetialTime old_time = _now_time;

		_now_time = DetialTime(_now_sec);

		if(old_time._min != _now_time._min)
		{
			on_next_min();
		}

		if(old_time._hour != _now_time._hour)
		{
			on_next_hour();
		}

		if(old_time._day != _now_time._day)
		{
			on_next_day();
		}

		cout << "on_timer_1000ms()" << endl;
	}

	void on_next_min()
	{
		cout << "on_next_min()" << endl;
	}

	void on_next_hour()
	{
		cout << "on_next_hour()" << endl;
	}

	void on_next_day()
	{
		cout << "on_next_day()" << endl;
	}

public:
	void on_init()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		int64 now_ms = tv.tv_sec*1000 + tv.tv_usec / 1000;

		{
			_now_time = DetialTime(tv.tv_sec);
			_now_sec = tv.tv_sec;
			_now_ms = now_ms;
		}


		TempTimerPtr time1(new TempTimer(boost::bind(&TimerModule::on_timer_100ms, this), now_ms+TIMER_DELAY_100MS, TIMER_DELAY_100MS));
		_timer_manager.add_timer(time1);
	}

	void start()
	{
		while(true)
		{
			struct timeval tv;

			gettimeofday(&tv, NULL);
			int64 now_ms = tv.tv_sec*1000 + tv.tv_usec / 1000;

			{
				_now_ms = now_ms;
				_now_sec = tv.tv_sec;
			}

			_timer_manager.update_time(now_ms);
			_timer_manager.run();
		}
	}
};



void timer_test()
{
	TimerModule one_module;

	one_module.on_init();

	one_module.start();
}




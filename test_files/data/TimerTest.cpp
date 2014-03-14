///*
// * TimerTest.cpp
// *
// *  Created on: Dec 30, 2013
// *      Author: root
// */
//
//#include "TimerTest.h"
//
//TimerTest::TimerTest()
//{
//	_id = 0;
//	_when = 0;
//	_interval_ms = 0;
//	_repeat = false;
//}
//
//TimerTest::TimerTest(int64 id, const TimerCallback & cb, int64 when_ms, int64 interval_ms)
//{
//	_id = id;
//	_when = when_ms;
//	_cb = cb;
//
//	_interval_ms = interval_ms;
//	_repeat = (interval_ms > 0);
//}
//
//TimerTest::~TimerTest()
//{
//
//}
//
//void TimerTest::run()const
//{
//	_cb();
//}
//
//void TimerTest::restart(int64 now_ms)
//{
//	if(is_repeat() == false)
//	{
//		return;
//	}
//
//	_when = now_ms + _interval_ms;
//}
//
//bool TimerTest::is_repeat()const
//{
//	return _repeat;
//}
//
//int64 TimerTest::id()const
//{
//	return _id;
//}
//
//time_t TimerTest::when()const
//{
//	return _when;
//}
//
//int64 TimerTest::interval()const
//{
//	return _interval_ms;
//}
//
//
//
//
///**  TimerManager  */
//ModuleTimerManager::ModuleTimerManager()
//{
//	_timer_id = 0;
//	_now_ms = 0;
//}
//
//ModuleTimerManager::~ModuleTimerManager()
//{
//
//}
//
//void ModuleTimerManager::run()
//{
//	typedef Timers::nth_index<1>::type AllTimers;
//
//	AllTimers * timers = &_timers.get<1>();
//
//	list<TimerPtr> restart_timers;
//
//	while(timers->empty() == false)
//	{
//		TimerPtr tmp_timer = *timers->begin();
//
//		if(tmp_timer->when() > _now_ms)
//		{
//			break;
//		}
//
//		timers->erase(timers->begin());
//
//		tmp_timer->run();
//
//		if(tmp_timer->is_repeat() == true)
//		{
//			restart_timers.push_back(tmp_timer);
//		}
//	}
//
//	foreach_iterator(iter, restart_timers.begin(), restart_timers.end())
//	{
//		TimerPtr one_timer = *iter;
//
//		one_timer->restart(_now_ms);
//
//		_timers.insert(one_timer);
//	}
//}
//
//
//void ModuleTimerManager::update_now_ms(int64 now_ms)
//{
//	_now_ms = now_ms;
//}
//
//int64 ModuleTimerManager::get_new_id()
//{
//	_timer_id++;
//
//	return _timer_id;
//}
//
//void ModuleTimerManager::run_every(int64 delay_ms, const TimerTest::TimerCallback & cb)
//{
//	if(delay_ms <= 0)
//	{
//		return;
//	}
//
//	int64 timer_id = get_new_id();
//
//	TimerPtr one_timer = new TimerTest(timer_id, cb, _now_ms+delay_ms, delay_ms);
//
//	_timers.insert(one_timer);
//}

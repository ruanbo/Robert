///*
// * TimerTest.h
// *
// *  Created on: Dec 30, 2013
// *      Author: root
// */
//
//#ifndef TIMERTEST_H_
//#define TIMERTEST_H_
//
//#include "Define.h"
//#include <boost/multi_index_container.hpp>
//#include <boost/multi_index/hashed_index.hpp>
//#include <boost/multi_index/mem_fun.hpp>
//#include <boost/multi_index/identity.hpp>
//#include <boost/multi_index/indexed_by.hpp>
//#include <boost/multi_index/ordered_index.hpp>
//
//using namespace boost::multi_index;
//
//static const int64 TIMER_DELAY_100MS = 100;
//
//
//class TimerTest : public smart_count
//{
//
//public:
//	typedef boost::function<void()> TimerCallback;
//
//private:
//	int64 _id;
//	int64 _when;
//	int64 _interval_ms;
//	bool _repeat;
//
//	TimerCallback _cb;
//
//
//public:
//	TimerTest();
//
//	TimerTest(int64 id, const TimerCallback & cb, int64 when_ms, int64 interval_ms = 0);
//
//	virtual ~TimerTest();
//
//	void run()const;
//
//	void restart(int64 now_ms);
//
//	bool is_repeat()const;
//
//	int64 id()const;
//
//	time_t when()const;
//
//	int64 interval()const;
//
//};
//
//typedef smart_ptr<TimerTest> TimerPtr;
//
//
//
//
//class ModuleTimerManager
//{
//typedef boost::multi_index_container<TimerPtr,
//			indexed_by<
//				hashed_unique<const_mem_fun<TimerTest, int64, &TimerTest::id> >,
//				ordered_non_unique<const_mem_fun<TimerTest, time_t, &TimerTest::when> >
//			>
//		> Timers;
//
//private:
//	int64 _timer_id;
//
//	int64 _now_ms;
//
//	Timers _timers;
//
//public:
//	ModuleTimerManager();
//
//	virtual ~ModuleTimerManager();
//
//private:
//
//public:
//	void run();
//
//	void update_now_ms(int64 now_ms);
//
//	int64 get_new_id();
//
//public:
//	void run_every(int64 delay_ms, const TimerTest::TimerCallback & cb);
//
//};
//
//
//
//#endif /* TIMERTEST_H_ */
//
//
////TimeStamp TimeStamp::now()
////{
////	struct timeval tv;
////
////	gettimeofday(&tv, NULL);
////
////	int64 micro_seconds = tv.tv_sec * MICROSECS_PER_SECOND + tv.tv_usec;
////
////	return TimeStamp(micro_seconds / MICROSECS_PER_MIILLISEC);
////}

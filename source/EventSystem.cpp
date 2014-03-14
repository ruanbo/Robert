/*
 * EventSystem.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: root
 */

#include "Define.h"

enum EventType
{
	ET_NONE = 0,

	ET_ONE = 1,
	ET_TWO =2,

	ET_END
};


class EventBase : public smart_count
{
private:
	EventType _type;

public:
	EventBase()
	{
		_type = ET_NONE;
	}
};

typedef smart_ptr<EventBase> EventBasePtr;


void event_handler()
{

}







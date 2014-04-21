/*
 * Facade.h
 *
 *  Created on: Apr 21, 2014
 *      Author: Robert
 */

#ifndef FACADE_H_
#define FACADE_H_

class Door
{
public:
	Door() {}
	~Door() {}
public:
	void open() {}
	void close() {}
};

class Light
{
public:
	Light() {}
	~Light() {}
public:
	void turn_on() {}
	void turn_off() {}
};

class Computer
{
public:
	Computer() {}
	~Computer() {}
public:
	void turn_on(){}
	void turn_off() {}
};

class Facade
{
private:
	Door *_door;
	Light *_light;
	Computer *_computer;

public:
	Facade()
	{
		_door = new Door();
		_light = new Light();
		_computer = new Computer();
	}
	virtual ~Facade()
	{
		if(_door)
		{
			delete _door;
		}
		if(_light)
		{
			delete _light;
		}
		if(_computer)
		{
			delete _computer;
		}
	}

public:
	void enter_office()
	{
		_door->open();
		_light->turn_on();
		_computer->turn_on();
	}
	void leave_office()
	{
		_computer->turn_off();
		_light->turn_off();
		_door->close();
	}
};

#endif /* FACADE_H_ */

/*
 * Proxy.h
 *
 *  Created on: Apr 21, 2014
 *      Author: Robert
 */

#ifndef PROXY_H_
#define PROXY_H_

class Subject
{
public:
	Subject() {}
	virtual ~Subject() {}
public:
	void request() {}
};

class RealSubject : public Subject
{
public:
	RealSubject() {}
	~RealSubject() {}
public:
	void real_request() {}
};


class Proxy : public Subject
{
private:
	Subject *_subject;
public:
	Proxy(Subject* subject)
	{
		this->_subject = subject;
	}
	virtual ~Proxy()
	{
		if(_subject)
		{
			delete _subject;
		}
	}

public:
	void before() {}
	void end() {}

	void request()
	{
		before();
		if(_subject)
		{
			_subject->request();
		}
		end();
	}
};
#endif /* PROXY_H_ */

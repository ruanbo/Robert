/*
 * Adapter.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Robert
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_


class Target
{
public:
	virtual ~Target() {}

	virtual void request() {}
};

class OneProduct
{
public:
	void request_one() {}
};



class Adapter : public Target, public OneProduct
{
public:
	Adapter();
	~Adapter();

	void request()
	{
		this->request_one();
	}
};


void adapter_pattern_test()
{
	Target *t = new Adapter();

	t->request();
}




#endif /* ADAPTER_H_ */

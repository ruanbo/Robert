/*
 * Prototype.h
 *
 *  Created on: Apr 16, 2014
 *      Author: Robert
 */

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_



class Prototype
{
public:
	Prototype();
	virtual ~Prototype();

	virtual Prototype* clone() = 0;
};


class Prototype1 : public Prototype
{
private:
	int _id;

public:
	Prototype1()
	{
		this->_id = 0;
	}
	Prototype1(const Prototype1& type)
	{
		this->_id = type._id;
	}


	Prototype* clone()
	{
		return new Prototype1(*this);
	}
};

class Prototype2 : public Prototype
{
private:
	int _id;

public:
	Prototype2()
	{
		this->_id = 0;
	}
	Prototype2(const Prototype2& type)
	{
		this->_id = type._id;
	}

	Prototype* clone()
	{
		return new Prototype2(*this);
	}
};






#endif /* PROTOTYPE_H_ */

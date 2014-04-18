/*
 * Builder.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Robert
 */

#ifndef BUILDER_H_
#define BUILDER_H_

class Builder
{
public:
	Builder();
	virtual ~Builder();

public:
	virtual void build_head() = 0;
	virtual void build_body() = 0;
	virtual void build_arm() = 0;
	virtual void build_leg() = 0;
};

class ThinBuilder : public Builder
{
public:
	void build_head() {}
	void build_body() {}
	void build_arm() {}
	void build_leg() {}
};

class FatBuilder : public Builder
{
public:
	void build_head() {}
	void build_body() {}
	void build_arm() {}
	void build_leg() {}
};


class Director
{
private:
	Builder *_builder;

public:
	void set_builder(Builder* builder)
	{
		_builder = builder;
	}

	void create()
	{
		_builder->build_head();
		_builder->build_body();
		_builder->build_arm();
		_builder->build_leg();
	}
};


void build_pattern_test()
{
	Director director;

	ThinBuilder *my_builder = new ThinBuilder();
//	FatBuilder *my_builder = new FatBuilder();

	director.set_builder(my_builder);
	director.create();

}





#endif /* BUILDER_H_ */

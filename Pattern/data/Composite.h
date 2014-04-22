/*
 * Composite.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Robert
 */

#ifndef COMPOSITE_H_
#define COMPOSITE_H_

#include <iostream>
#include <stdlib.h>
#include <vector>


class Component
{
private:
	std::string _name;

public:
	Component() { _name = ""; }
	virtual ~Component() {}

public:
	virtual void operation() = 0;

	virtual void add(Component *component) { }

	virtual void del(const std::string& name) { }

	virtual Component* get_child(const std::string& name) { return NULL; }

	std::string get_name()
	{
		return _name;
	}
};

class Leaf : public Component
{
public:
	Leaf() {}
	~Leaf() {}

public:
	void operation()
	{
		std::cout << "a leaf operation" << std::endl;
	}
};



class Composite : public Component
{
private:
	std::vector<Component*> _components;

public:
	Composite()
	{

	}
	virtual ~Composite()
	{
		_components.clear();
	}

public:
	void operation()
	{

	}

	void add(Component* component)
	{
		_components.push_back(component);
	}

	void del(const std::string& name)
	{
		std::vector<Component*>::iterator iter = _components.begin();
		for(; iter!=_components.end(); ++iter)
		{
			Component* component = *iter;
			if(component->get_name() == name)
			{
				_components.erase(iter);
			}
		}
	}

	Component* get_child(const std::string& name)
	{
		std::vector<Component*>::iterator iter = _components.begin();
		for(; iter!=_components.end(); ++iter)
		{
			Component* component = *iter;
			if(component->get_name() == name)
			{
				return component;
			}
		}
		return NULL;
	}
};

#endif /* COMPOSITE_H_ */

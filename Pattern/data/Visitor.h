/*
 * Visitor.h
 *
 *  Created on: May 13, 2014
 *      Author: Robert
 */

#ifndef VISITOR_H_
#define VISITOR_H_

#include "common/Define.h"

class Element;

class Visitor
{
public:
	Visitor();
	virtual ~Visitor();
public:
	virtual void visit(Element *element) = 0;
};

class Element
{
public:
	Element() {}
	virtual ~Element() {}
public:
	virtual void accept(Visitor *visitor) = 0;
};

class Employee : public Element
{
public:
	string _name;
	double _income;
	int _vacation;

public:
	Employee(const string& name, double income, int vacation)
	{
		this->_name = name;
		this->_income = income;
		this->_vacation = vacation;
	}
	void accept(Visitor *visitor)
	{
		visitor->visit(this);
	}
};

class IncomeVisitor : public Visitor
{
public:
	void visit(Element *element)
	{
		Employee *employee = (Employee*)element;
		if(employee != NULL)
		{
			employee->_income *= 1.20;
			cout << employee->_name << " new income:" << employee->_income << endl;
		}
	}
};

class VacationVisitor : public Visitor
{
public:
	void visit(Element *element)
	{
		Employee *employee = (Employee*)element;
		if(employee != NULL)
		{
			employee->_vacation += 10;

			cout << employee->_name << " now vacation:" << employee->_vacation << endl;
		}
	}
};

class Employees
{
private:
	list<Employee*> _employees;
public:
	void attach(Employee *employee)
	{
		_employees.push_back(employee);
	}
	void detach(Employee *employee)
	{
		_employees.remove(employee);
	}
	void accept(Visitor *visitor)
	{
		for(list<Employee*>::iterator iter=_employees.begin(); iter!=_employees.end(); ++iter)
		{
			(*iter)->accept(visitor);
		}
	}
};















#endif /* VISITOR_H_ */

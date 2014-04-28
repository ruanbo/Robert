/*
 * strategy.h
 *
 *  Created on: Apr 28, 2014
 *      Author: Robert
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "common/Define.h"

class SalaryComput
{
public:
	SalaryComput() {}
	virtual ~SalaryComput() {}

public:
	virtual void do_salary() = 0;
};

class HrSalary : public SalaryComput
{
public:
	HrSalary() {}
	~HrSalary() {}

public:
	void do_salary()
	{
		cout << "计算Hr薪资" << endl;
	}
};

class DevelopSalary : public SalaryComput
{
public:
	DevelopSalary() {}
	~DevelopSalary() {}

public:
	void do_salary()
	{
		cout << "计算开发薪资" << endl;
	}
};

class Strategy
{
public:
	Strategy();
	virtual ~Strategy();

public:
	void compute_salary(SalaryComput *salary)
	{
		salary->do_salary();
	}
};

void pattern_strategy_test()
{
	Strategy* company = new Strategy();

	HrSalary *hr_salary = new HrSalary();
	company->compute_salary(hr_salary);

	DevelopSalary *develop_salary = new DevelopSalary();
	company->compute_salary(develop_salary);

	delete develop_salary;
	delete hr_salary;
	delete company;
}

#endif /* STRATEGY_H_ */

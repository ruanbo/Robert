/*
 * Bridge.h
 *
 *  Created on: Apr 26, 2014
 *      Author: Robert
 */

#ifndef BRIDGE_H_
#define BRIDGE_H_


class OS
{
public:
	OS() {}
	virtual ~OS() {}
public:
	virtual void install_os() = 0;
};

class WindowsOS : public OS
{
public:
	WindowsOS() {}
	~WindowsOS() {}
public:
	void install_os()
	{

	}
};

class LinuxOS : public OS
{
public:
	LinuxOS() {}
	~LinuxOS() {}
public:
	void install_os()
	{

	}
};



class Computer
{
protected:
	OS* _os;
public:
	Computer(OS *os)
	{
		_os = os;
	}
	virtual ~Computer()
	{
//		if(_os) delete _os;
	}
public:
	virtual void install() = 0;

};

class LenovoComputer : public Computer
{
public:
	LenovoComputer(OS *os) : Computer(os) {}
	~LenovoComputer() {}
public:
	void install()
	{
		_os->install_os();
	}
};

class AppleComputer : public Computer
{
public:
	AppleComputer(OS *os) : Computer(os) {}
	~AppleComputer() {}
public:
	void install()
	{
		_os->install_os();
	}
};


void pattern_bridge_test()
{
	OS *win_os = new WindowsOS();
	Computer *apple_computer = new AppleComputer(win_os);

	apple_computer->install();

	delete apple_computer;
	delete win_os;
}


#endif /* BRIDGE_H_ */

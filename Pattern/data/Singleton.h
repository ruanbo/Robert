/*
 * Singleton.h
 *
 *  Created on: Apr 12, 2014
 *      Author: root
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <cstdlib>

// 饿汉模式, 无论是否调用该类的实例，在程序开始时就会产生一个该类的实例，在以后仅返回这个实例
// 这种方法是线程安全的，因为静态实例的初始化在程序进入主函数之前就由主线程以单线程方式完成了初始化
// 主程序结束后，不会自动调用析构函数
class Singleton0
{
private:
	static Singleton0* _instance;
	Singleton0();

public:
	virtual ~Singleton0();

public:
	static Singleton0* get_instance();

	void show();
};



// 懒汉模式:静态成员变量
// 主程序结束后，不自动调用析构函数
class Singleton1
{
private:
	static Singleton1 * _instance;

	Singleton1();

public:
	virtual ~Singleton1();

public:
	static Singleton1* get_instance();


	void show();
};

// 懒汉模式:静态成员变量. 加了创建实例时的线程控制，避免创建出多个实例
// 主程序结束后，不会自动调用析构函数
class Singleton2
{
private:
	static Singleton2* _instance;
	Singleton2();

public:
	virtual ~Singleton2();

public:
	static Singleton2* get_instance();

	void show();
};

// 懒汉模式：内部静态实例
// 主程序结束后，会自动调用析构函数
class Singleton3
{
private:
	Singleton3();

public:
	virtual ~Singleton3();

public:
	static Singleton3* get_instance();

	void show();
};



// 来个文艺版的，加个辅助的垃圾回收类
class Singleton4
{
private:
	class Garbage;

	static Singleton4* _instance;
	static Garbage _garbage;

	Singleton4();

	class Garbage
	{
	public:
		Garbage()
		{

		}
		~Garbage()
		{
			if(Singleton4::_instance != NULL)
			{
				delete Singleton4::_instance;
			}
		}
	};

public:
	~Singleton4();

	static Singleton4 * get_instance();

	void show();
};









#endif /* SINGLETON_H_ */

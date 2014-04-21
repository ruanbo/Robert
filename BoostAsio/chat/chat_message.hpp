/*
 * char_message.hpp
 *
 *  Created on: Mar 14, 2014
 *      Author: root
 */

#ifndef CHAR_MESSAGE_HPP_
#define CHAR_MESSAGE_HPP_


#include "Define.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>


class chat_message
{
public:
	enum { header_length = 4 };
	enum { max_body_len = 512 };

private:
	size_t _body_length;
	char _data[header_length + max_body_len];

public:
	chat_message() : _body_length(0)
	{

	}

	virtual ~chat_message()
	{

	}

public:
	const char* data()const
	{
		return _data;
	}

	char* data()
	{
		return _data;
	}

	size_t length()const
	{
		return header_length + _body_length;
	}

	const char* body()const
	{
		return _data + header_length;
	}

	char* body()
	{
		return _data + header_length;
	}
	size_t body_length()const
	{
		return _body_length;
	}

	void body_length(size_t length)
	{
		_body_length = length;
		if(_body_length > max_body_len)
		{
			_body_length = max_body_len;
		}
	}

	bool decode_header()
	{
		using namespace std;
		char header[header_length+1] = "";
		strncat(header, _data, header_length);
		_body_length = atoi(header);

		if(_body_length > max_body_len)
		{
			_body_length = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		using namespace std;

		char header[header_length + 1] = "";
		sprintf(header, "%4d", _body_length);
		memcpy(_data, header, header_length);
	}
};




#endif /* CHAR_MESSAGE_HPP_ */

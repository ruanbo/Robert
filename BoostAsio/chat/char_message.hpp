/*
 * char_message.hpp
 *
 *  Created on: Mar 14, 2014
 *      Author: root
 */

#ifndef CHAR_MESSAGE_HPP_
#define CHAR_MESSAGE_HPP_


#include "Define.h"

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
};




#endif /* CHAR_MESSAGE_HPP_ */

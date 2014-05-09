/*
 * MultiProcessHeader.h
 *
 *  Created on: May 8, 2014
 *      Author: Robert
 */

#ifndef MULTIPROCESSHEADER_H_
#define MULTIPROCESSHEADER_H_


#include "common/Define.h"
#include "common/TypesDef.h"


enum ProcessType
{
	PT_NONE = 0,

	PT_LOGIN = 1,
	PT_LOGIC = 2,

	PT_END
};


void multi_process_first();

void process_entry(ProcessType type);




#endif /* MULTIPROCESSHEADER_H_ */

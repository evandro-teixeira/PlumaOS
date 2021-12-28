/*
 * List.h
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_LIST_H_
#define PLUMAOS_LIST_H_

#include "PlumaOS_Types.h"

typedef struct
{
	PlumaOS_ptrTask_t task;
	PlumaOS_StateTask_t state;
	uint32_t pausedtime;
	PlumaOS_PriorityTask_t Priority;
	PlumaOS_kernelTask_t task_status;
}strTask_t;

typedef struct no
{
	uint8_t index;
	strTask_t param;
	struct no * next;
}noList_t;


noList_t* List_Init(void);
noList_t* List_Insert(noList_t* list, uint8_t index, strTask_t param);
noList_t* List_Get(noList_t* list, uint8_t index);
noList_t* List_Remove(noList_t* list, uint8_t index, uint8_t max);
void List_Delete(noList_t* list);


#endif /* PLUMAOS_LIST_H_ */

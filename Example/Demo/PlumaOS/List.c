/*
 * List.c
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#include <stdlib.h>
#include "List.h"


/**
 * @brief
 */
noList_t* List_Init(void)
{
	return PlumaOS_Null;
}

/**
 *
 */
noList_t* List_Insert(noList_t* list, uint8_t index, strTask_t param)
{
	static noList_t* init_no;
	noList_t* new_no = (noList_t*)malloc(sizeof(noList_t));

	if(list == PlumaOS_Null)
	{
		init_no = new_no;
	}
	else
	{
		list->next = new_no;
	}

	new_no->index = index;
	new_no->param = param;
	new_no->next = init_no;
	return new_no;
}

/**
 *
 */
noList_t* List_Get(noList_t* list, uint8_t index)
{
	noList_t* item;
	for(item = list; item != PlumaOS_Null; item = item->next)
	{
		if(item->index == index)
			return item;
	}
	return PlumaOS_Null;
}

/**
 *
 */
noList_t* List_Remove(noList_t* list, uint8_t index, uint8_t max)
{
	uint8_t i = 0;
	noList_t* previous;
	noList_t* item = list;

	for(i=1;i<(max+1);i++)
	{
		previous = item;
		if(item->index == index)
		{
			item = item->next;
			break;
		}
		//previous = item;
		item = item->next;
	}
	if(i > max)
	{
		return list;
	}
	else
	{
		noList_t* no = item;
		for(i=1;i<(max+1);i++)
		{
			if(no->next == previous)
			{
				no->next = previous->next;
				break;
			}
			no = no->next;
		}
		if(i > max)
		{
			return list;
		}

		free(previous);
		previous->next = item->next;
		return no;
	}
}

/**
 *
 */
void List_Delete(noList_t* list)
{
	noList_t* aux = list;
	while(aux != PlumaOS_Null)
	{
		noList_t* no_next = aux->next;
		free(aux);
		aux = no_next;
	}
}

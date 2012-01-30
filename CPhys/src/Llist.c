/*
 * Llist.c
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#include "Llist.h"
#include <malloc.h>

Llist_t * Llist_new(Llist_t * ll)
{
	Llist_t * ret = malloc(sizeof(Llist_t));
	if(!ll)
	{
		ret->next = NULL;
		ret->data = NULL;
	}
	else
	{
		ret->next = ll->next;
		ret->data = ll->data;
	}

	return ret;
}
Llist_t * Llist_Init(Llist_t * ll, Llist_t * next, void * data)
{
	if(!ll)
		ll = malloc(sizeof(Llist_t));

	ll->next = next;
	ll->data = data;

	return ll;
}
Llist_t * Llist_fInit(Llist_t * next, void * data)
{
	Llist_t * ret = malloc(sizeof(Llist_t));
	ret->data = data;
	ret->next = next;

	return ret;
}
Llist_t * Llist_Prepend(Llist_t * ll, void * data)
{
	Llist_t * tmp = ll->next;
	ll->next = Llist_fInit(tmp,data);
	return ll->next;
}

Llist_t * Llist_Next(Llist_t * ll)
{
	return ll->next;
}
void * Llist_Data(Llist_t * ll)
{
	return ll->data;
}

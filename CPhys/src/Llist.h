/*
 * Llist.h
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#ifndef LLIST_H_
#define LLIST_H_

typedef struct Llist_s
{
	struct Llist_s * next;
	void * data;
} Llist_t;


Llist_t * Llist_new(Llist_t * ll);
Llist_t * Llist_Init(Llist_t * ll, Llist_t * next, void * data);
Llist_t * Llist_fInit(Llist_t * next, void * data);
Llist_t * Llist_Prepend(Llist_t * ll, void * data);
Llist_t * Llist_Next(Llist_t * ll);
void * Llist_Data(Llist_t * ll);

#endif /* LLIST_H_ */

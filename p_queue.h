/******************************************************************************
 Project: 	Priority queue
 Author: 	Eli Feinshtein
 Date: 		3/11/22
 Version: 1.0
*******************************************************************************/
#ifndef __P_QUEUE_H__
#define __P_QUEUE_H__

#include <stddef.h> /*size_t*/

#include "sort_list.h"




typedef struct p_que p_que_ty;


/* Description: Creates a new priority queue.
   Arguments:	cmp_func- user defined prioritized function
   Return: 		Pointer to new priority queue or NULL on memory 
   				allocation fail.
   Complexity: 	O(1). 
   Undefined behavior: none
   Notes : cmp_func- return == 0 if data1 equal data2,  return < 0 if data1 
   lower then data2, return > 0 if data1 higher then data2*/
p_que_ty *PQueueCreate(int (*cmp_func)(const void *data1,const void *data2)); 

/* Description: Frees a priority queue.
   Arguments: 	p_que_ty pointer pointing to queue to be freed.
   Return: 		void
   Complexity: 	O(n). n num of elements in the list
   Undefined behavior: 	Invalid pointer*/
void PQueueDestroy(p_que_ty *p_que);

  /*Description: insert an element to the queue by its priority.
	Arguments:	 p_que - a pointer to the queue.
    	   		 data -the data that the element will hold.
	Return: 	 0 if the node successfully inserted, non 0 on fail.
	Complexity : on succsess - O(n) n is the number of elemnts in the queue
	Undefine behavior : invalide p_que_ty pointer
	Notes: if the new element has an equal priority to an existing element the 
	order is undefined*/
int PQueueNq(p_que_ty *p_que, const void *data); 

/* Description: Removes the member with the highest priority.
   Arguments:	a pointer to the queue
   Return: 		return the data of the dequeued element.
   Complexity : O(1)
   Undefine behavior :	invalide queue pointer  dequeuing into an empty queue*/
void *PQueueDq(p_que_ty *p_que);

/* Description: get the data of the element with the highest priority.
   Arguments: 	a pointer to the queue
   Return: 		the data held by the highest priority element.
   Complexity : O(1)
   Undefine behavior :	invalid queue pointer Peeking into an empty queue or end
   						DUMMY*/
void *PQueuePeek(const p_que_ty *p_que);

/* Description: count the number of elements in the queue.
   Arguments: 	a pointer to the queue
   Return: 		the number of elements in the queue.
   Complexity : O(n)  n is number of elements. 
   Undefine behavior : invalid queue pointer */
size_t PQueueSize(const p_que_ty *p_que);

/* Description: check if the queue is empty.
   Arguments: 	a pointer to the queue
   Return: 		1 if the queue is empty and 0 if the queue has nodes.
   Complexity : O(1)
   Undefine behavior : invalid queue pointer */
int PQueueIsEmpty(const p_que_ty *p_que);

/* Description: Clear all elements from the priority queue. leaves an empty queue
   Arguments: 	p_que - que to clear pri from.
   Return:		non
   Complexity :	O(n)  n is number of elements. 
   Undefine behavior : invalide queue pointer */
void PQueueClear(p_que_ty *p_que);

/* Description: Erase the first occurance (with the highest priority) that 
				matches according to 'match_func' condition. 
   Arguments:  	p_que - pointer to priority queue.
   				match_func - pointer to user implemented matching func.
   				param - used by 'match_func' to perform the condition.    
   Return: 		returns the data that was erased, if there is no match returns 
   				NULL. 
   Complexity :	O(n)  n is number of elements to erase. 
   Undefine behavior : invalide queue pointer, 
   Notes:		match_function should returns 0 if a match is found.
   			 	else, if not a match*/ 
void *PQueueErase(p_que_ty *p_que, int(*match_func)
				 (const void *data, const void *param), const void *param);	

#endif /* __P_QUEUE_H__*/



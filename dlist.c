/******************************************************************************
* Project: 	Doubly Linked List
* Author: 	Eli feinshtein	
* Date: 	27/10/2022
* Version:	1.0 
*******************************************************************************/
#include <stddef.h> /* size_t*/
#include <stdlib.h> /* malloc ,free*/
#include <assert.h> /* assert */
#include <stdio.h> /* fputs */

#include "dlist.h"
#include "utils.h"


/****************************       usefull defines				***************/

#define CURR curr_iter.dlist_node
#define NEXT curr_iter.dlist_node ->next
#define PREV curr_iter.dlist_node ->prev
#define HEAD dlist ->head
#define TAIL dlist ->tail



enum return_val 
{
	SUCCESS = 0,
	FALSE = 0,
	FAIL = 1,
	TRUE = 1,
	MEMALLOCFAIL = -1
}; 

/*************************		MAIN STRUCTS		***************************/

struct dlist_node
{
	void *data;
	dlist_node_ty *next;
	dlist_node_ty *prev;
};

struct dlist
{
	dlist_node_ty head;
	dlist_node_ty tail;
};

/****************************       FORWARD DECLARATIONS		***************/
static void *CreateNode( const void *data, void *next , void *prev);
static dlist_iter_ty ReturnEndDummy( dlist_node_ty *curr_item);
static int CountParam(void *data, const void *param);
static void InitDlist(dlist_ty *dlist);

/******************************************************************************/

dlist_ty *DListCreate(void)
{
	dlist_ty *dlist = NULL;
	
	/* tallocate memory for the slist */
	dlist = (dlist_ty *) malloc( sizeof(dlist_ty) );
	
	/* test if malloc succeeded */
	MALLOC_TEST( dlist == NULL , NULL, "alloc fail",  NULL,  NULL);
	
	/* initialize the dlist */ 
	InitDlist(dlist);
	
	return dlist;
}


void DListDestroy(dlist_ty *dlist)
{
	/* create and initiate a  helper iterator with current head pointer*/
	dlist_node_ty *node_to_free = NULL;
	dlist_node_ty *next_node = NULL;
	
	assert(dlist && "dlist isn't valid");
	
	node_to_free = dlist -> head.next ;
	
	while(NULL != node_to_free ->next)
	{
		/* update next_node */
		next_node = node_to_free -> next;  
		 
		/* free previous head ppinter */
		free(node_to_free);
		
		/* updtate the helper iterator to be the current node */
		node_to_free = next_node;
	}
	
	/* free the memory allocated to the main struct */
	free(dlist);
	dlist = NULL;
}



size_t DListSize(const dlist_ty *dlist) 
{
	size_t counter = 0;
	
	assert(dlist && "dlist isn't valid");
	
	/* check if the list is not empty - if it is, return 0 */
	if(HEAD.next == &TAIL)
	{
		return counter;
	}
	
	/* run FOREACH function wiith counter function */
	DListForEach( DListBegin(dlist), DListEnd(dlist) ,CountParam, &counter); 
	
	return counter;
}


int DListIsEmpty(const dlist_ty *dlist) 
{
	assert(dlist && "dlist isn't valid");
	
	/* if size returns number - not makes it 0, and if 0 it will return 1 */
	return !DListSize(dlist);
}


dlist_iter_ty DListBegin(const dlist_ty *dlist)
{
	dlist_iter_ty return_iter = {NULL};
	
	assert(dlist && "dlist isn't valid");
	
	/* assign the iterator to point on the start of the dlist - head node */
	return_iter.dlist_node = dlist -> head.next;
	
	return return_iter;
}


dlist_iter_ty DListEnd(const dlist_ty *dlist)
{
	dlist_iter_ty return_iter = {NULL};
	
	assert(dlist && "dlist isn't valid");
	
	/* assign the iterator to point on the end of the dlist - tail node */
	return_iter.dlist_node = (dlist_node_ty *)&dlist -> tail; 
	
	return return_iter;	
}


dlist_iter_ty DListNext(const dlist_iter_ty curr_iter)
{	
	dlist_iter_ty return_iter = {NULL};
	
	assert(CURR && "iterator is not valid");
	
	/* assign to return_iter to the adress of pevious node */
	return_iter.dlist_node = NEXT;
	
	return return_iter;
}


dlist_iter_ty DListPrev(const dlist_iter_ty curr_iter)
{	
	dlist_iter_ty return_iter = {NULL};
	
	assert(CURR && "iterator is not valid");
	
	/* assign return_iter to the adress of pevious node */
	return_iter.dlist_node = PREV;
	
	return return_iter;
}


void *DListGetData(const dlist_iter_ty curr_iter)
{
	assert(CURR && "iterator is not valid");
	
	/* return the adress of data stored in the current node struct */
	return CURR -> data;
}


int DListIsSameIter(const dlist_iter_ty iter1, const dlist_iter_ty iter2)
{
	assert(iter1.dlist_node  && "iterator1 isn't valid");	
	assert(iter2.dlist_node  && "iterator1 isn't valid");
	
	/* return 1 if they are equal, and 0 otherwise */
	return iter1.dlist_node  == iter2.dlist_node ? TRUE : FALSE ; 
}


dlist_iter_ty DListInsert(dlist_iter_ty curr_iter, const void *data)
{
	dlist_node_ty *new_node  = CreateNode(data, CURR, PREV);
	
	assert(CURR && "iterator is not valid");
	
	/* test if malloc succeeded, if not - return end DUMMY */
	if(NULL == new_node)
	{
		return ReturnEndDummy( curr_iter.dlist_node);
	}
	
	/* point previous node to the new node we created */
	CURR ->prev -> next = new_node;
	
	/* point the prev ptr of next node to the new node we created */
	CURR ->prev = new_node;
	
	/* poit the iterator to the new_node */
	CURR = new_node;
	
	return curr_iter;
}


dlist_iter_ty DListRemove(dlist_iter_ty curr_iter)
{
	dlist_iter_ty return_iter = {NULL};
	
	assert(CURR && "iterator is not valid");

	NEXT -> prev = PREV; 
	PREV -> next = NEXT;
	
	/* store the adress of new current pointer to return iterator */
	return_iter.dlist_node = NEXT;
	
	/* delete next element */	
	free(CURR);
	
	return return_iter;	
}


dlist_iter_ty DListPushFront(dlist_ty *dlist, const void *data)
{	
	assert(dlist && "dlist isn't valid");
	
	return DListInsert(DListBegin(dlist), data);
}


dlist_iter_ty DListPushBack(dlist_ty *dlist, const void *data)
{
	assert(dlist && "dlist isn't valid");
	
	return DListInsert(DListEnd(dlist), data);
}


void *DListPopFront(dlist_ty *dlist)
{	
	void *popped_data = NULL;
	
	assert(dlist && "dlist isn't valid");
	
	/* store the popped data in temporary storage */
	popped_data = HEAD.next -> data;
	
	DListRemove(DListBegin(dlist));
	
	return popped_data;	
}


void *DListPopBack(dlist_ty *dlist)
{	
	void *popped_data = NULL;
	
	assert(dlist && "dlist isn't valid");
	
	/* store the popped data in temporary storage */
	popped_data = TAIL.prev -> data;
	
	DListRemove(DListPrev(DListEnd(dlist)));
	
	return popped_data;	
}


int DListForEach(dlist_iter_ty from, dlist_iter_ty to,
				  action_func_ty action_func, const void *param)
{
	assert(from.dlist_node);
	assert(to.dlist_node);
	assert(action_func);

	/* run untill current iter reaches the to iter */
	while( !DListIsSameIter( to, from) ) 
	{	
		/* call action func for current data and test if it succeeded */	
		if(FAIL == action_func( (from.dlist_node -> data), (void*)param))
		{
			return FAIL;
		}
		
		/* go to the next node */		
		from = DListNext(from);
	}

	return SUCCESS;
}


dlist_iter_ty DListFind(dlist_iter_ty from, dlist_iter_ty to,
						match_func_ty match_func, const void *param)
{	
	assert(from.dlist_node);
	assert(to.dlist_node);
	assert(match_func);
	
	/* while we didnt reach the "to" iterator */
	while( !DListIsSameIter( to, from ) ) 
	{		
		/* return the corresponding iterator if match is found */
		if( 0 == match_func( (from.dlist_node ->data), (void*)param) ) 
		{
			return from;
		}
		
		/* go to the next node */
		from = DListNext(from);
	}

	return ReturnEndDummy( to.dlist_node);
}



dlist_iter_ty DListSplice(dlist_iter_ty where, dlist_iter_ty from,
						  dlist_iter_ty to)
{
	dlist_node_ty *node_before_to = to.dlist_node ->prev;
		
	assert(where.dlist_node);
	assert(from.dlist_node);
	assert(to.dlist_node);
	
	if(DListIsSameIter(from,to))
	{
		return to;
	}
	
	/*update node before "from" to point "to"*/
	from.dlist_node ->prev->next = to.dlist_node;
	
	/*update node after "to" to prev point node before "from"*/
	to.dlist_node ->prev = from.dlist_node->prev;
	
	/*update node before where to point to from*/
	where.dlist_node ->prev ->next = from.dlist_node;
	
	/*update from node to point to node before where*/
	from.dlist_node ->prev = where.dlist_node->prev;

	/*update where prev to point node before "to" */
	where.dlist_node ->prev = node_before_to;
	
	/*update node before "to" to point where*/
	node_before_to ->next = where.dlist_node;
	
	/*return iterator to end of spliced section*/
	return to;

}


int DListMultiFind( dlist_iter_ty from, dlist_iter_ty to,
				   match_func_ty match_func, const void *param,
				    dlist_ty *output_list)
{
	int match_counter = 0;
	dlist_iter_ty curr_iter = {NULL};
	
	assert(from.dlist_node);
	assert(to.dlist_node);
	assert(param);
	assert(match_func);
	
	/* while we didnt reach the "to" iterator */
	while( !DListIsSameIter( to, from ) ) 
	{		
		if( 0 == match_func( (from.dlist_node ->data), (void*)param) )
		{
			/* increment the match counter */
			++match_counter;
			
			/* push the matching data to the output list */
			curr_iter = DListPushBack(output_list, from.dlist_node ->data );
			
			/* test if malloc succeeded */
			if(NULL == NEXT)
			{
				return MEMALLOCFAIL;
			}
		}
		
		/* go to the next node */
		from = DListNext(from);
	}

	return match_counter;
}




/**************** 			HELPER FUNCTIONS 	  	  *************************/
static void *CreateNode( const void *data, void *next , void *prev)
{
	dlist_node_ty *new_node = (dlist_node_ty *)malloc( sizeof(dlist_node_ty) );
	
	MALLOC_TEST( new_node == NULL , NULL, "alloc fail",  NULL,  NULL);
	
	new_node -> data = (void *)data;
	new_node -> next = next;
	new_node -> prev = prev;
	
	return new_node;
}


static void InitDlist(dlist_ty *dlist)
{
	HEAD.data = dlist;
	HEAD.next = &TAIL;
	HEAD.prev = NULL;
	
	TAIL.data = dlist;
	TAIL.next = NULL;
	TAIL.prev = &HEAD;
}

static dlist_iter_ty ReturnEndDummy( dlist_node_ty *item)
{
	dlist_iter_ty dummy = {NULL};
	
	dummy.dlist_node = item;
	
/*	if not - find the tail dummy and return it */
	while( dummy.dlist_node -> next)
	{
		dummy = DListNext(dummy);
	}
	
	return dummy;
	
}


static int CountParam(void *data, const void *param) 
{
	UNUSED(data); 
	*(int*)param += 1;	
	
	return SUCCESS;
}


/******************************************************************************
 Project: 	Priority queue
 Author: 	Eli Feinshtein
 Date: 		3/11/2022
 Version: 1.0
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc ,free */
#include <assert.h> /* assert */

#include "p_queue.h"
#include "utils.h"

#define SORTLIST this -> sort_list

enum return_val 
{
	SUCCESS = 0,	
	FAIL = 1	
}; 

enum
{
	FALSE = 0,
	TRUE = 1
};

/*************************		MAIN STRUCTS		***************************/

struct p_que
{
	sort_list_ty *sort_list; 
};

/****************************       FORWARD DECLARATIONS		***************/



/******************************************************************************/


p_que_ty *PQueueCreate(int (*cmp_func)(const void *data1,const void *data2))
{
	p_que_ty *p_que = NULL;
	
	/* tallocate memory for the slist */
	p_que = (p_que_ty *) malloc( sizeof(p_que_ty ) );
	
	/* test if malloc succeeded */
	MALLOC_TEST( p_que == NULL , NULL, "alloc fail",  NULL,  NULL)
	
	/* initialize the dlist */ 
	
	p_que -> sort_list = SortListCreate(cmp_func);
	
	/* test if malloc succeeded */
	MALLOC_TEST( p_que->sort_list == NULL , NULL, "alloc fail",  p_que,  NULL)
	
	return p_que;
}


void PQueueDestroy(p_que_ty *this)
{
	assert(this && "p_queue isn't valid");
	
	/* destroy the this -> sort_list*/
	SortListDestroy( SORTLIST);
	SORTLIST = NULL;
	
	/* free the p_que struct */
	free(this);
	this = NULL;
}


int PQueueNq(p_que_ty *this, const void *data)
{
	sort_list_iter_ty end = { NULL};
	sort_list_iter_ty insert = { NULL};
	
	/* assert the p_queu list is valid */
	assert( this && "p_queue isn't valid");
	
	/* assign the iterator to end of the list */
	end = SortListEnd( SORTLIST);
	
	/* assign the insert iterator to return iterator of Insert function */
	insert = SortListInsert( SORTLIST, data);
	
	/* if the insert iterator is not end dummy - we succeeded to enqueue */	
	return SortListIterIsEqual(end,insert) ? FAIL : SUCCESS ;
}


void *PQueueDq(p_que_ty *this)
{
	/* assert the p_queu list is valid */
	assert( this && "p_queue isn't valid");
	
	/* use the pop back function as the highest priority data is in the end */
	return SortListPopFront( SORTLIST);
}



void *PQueuePeek(const p_que_ty *this)
{
	/* assert the p_queu list is valid */
	assert( this && "p_queue isn't valid");
	
	return SortListGetData( SortListBegin( SORTLIST));
}


size_t PQueueSize(const p_que_ty *this)
{	
	/* assert the p_queu list is valid */
	assert( this && "p_queue isn't valid");
	
	return SortListSize( SORTLIST);
}


int PQueueIsEmpty(const p_que_ty *this)
{
	return SortListIsEmpty(SORTLIST);
}



void PQueueClear(p_que_ty *this)
{	
	sort_list_iter_ty curr = { NULL};
	sort_list_iter_ty end = { NULL};
	
	/* assert the p_queu list is valid */
	assert( this && "p_queue isn't valid");
		
	/*assign curr to the beginning of the list*/
	curr =  SortListBegin( SORTLIST);
	
	/*assign end to the last valid node */
	end = SortListPrev( SortListEnd( SORTLIST));

	/* run untill list end or while user data smaller than current data*/
	while( FALSE == SortListIterIsEqual( curr, end) )
	{			
		curr =  SortListRemove(curr);
	}
	
	SortListRemove(curr);
}


void *PQueueErase(p_que_ty *this, int(*match_func)
				 (const void *data, const void *param), const void *param)
{
	sort_list_iter_ty erase_iter = { NULL};
	sort_list_iter_ty start = { NULL};
	sort_list_iter_ty end = { NULL};
	
	void *erased_data = NULL;
	
	/* assert the p_queu list is valid */
	assert( this && "p_queue isn't valid");
	
	start = SortListBegin( SORTLIST);
	end = SortListEnd( SORTLIST);
	
	erase_iter = SortListFindIf( start, end, match_func, param);
	
	/* check if param was found, if not - return NULL */
	if( SortListIterIsEqual(erase_iter, end))
	{
		return NULL;
	}
	
	erased_data = SortListGetData( erase_iter);
	
	SortListRemove( erase_iter);
	
	return erased_data;
}	


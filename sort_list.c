/******************************************************************************
* Project: 	Sorted  List
* Author: 	Eli Feinshtein
* Date: 	1/11/22
* Version:	1.0 
*******************************************************************************/
#include <stddef.h> /* size_t*/
#include <stdlib.h> /* malloc ,free*/
#include <assert.h> /* assert */

#include "dlist.h"
#include "sort_list.h"


/********************      usefull defines and enum				***************/

#define DLIST this -> dlist
#define CMP this -> cmp_func 
#define ITER curr_iter.dlist_iter

enum return_val 
{
	SUCCESS = 0,	
	FAIL = 1,	
	MEMALLOCFAIL = -1
}; 

enum
{
	FALSE = 0,
	TRUE = 1
};

/*************************		MAIN STRUCTS		***************************/

struct sort_list
{
	dlist_ty *dlist;  
	cmp_func_ty cmp_func;
};

/****************************       FORWARD DECLARATIONS		***************/

static sort_list_ty *InitSortlist( sort_list_ty *this, cmp_func_ty cmp_func);

/******************************************************************************/


sort_list_ty *SortListCreate( cmp_func_ty cmp_func)
{
	sort_list_ty *sort_list = NULL;
	
	/* tallocate memory for the slist */
	sort_list = (sort_list_ty *) malloc( sizeof(sort_list_ty ) );
	
	/* test if malloc succeeded */
	MALLOC_TEST( sort_list == NULL , NULL, "alloc fail",  NULL,  NULL)
	
	/* initialize the dlist */ 
	InitSortlist(sort_list, cmp_func);
	
	return sort_list;
}



void SortListDestroy( sort_list_ty *this)
{
	assert(this && "sort_list isn't valid");
	
	/* destroy the this -> dlist */
	DListDestroy( DLIST);
	DLIST = NULL;
	
	free(this);
	this = NULL;
}


size_t SortListSize( const sort_list_ty *this)
{
	assert(this && "sort_list isn't valid");
	
	return DListSize( DLIST);	
}



int SortListIsEmpty( const sort_list_ty *this)
{
	assert(this && "sort_list isn't valid");
	
	/* if size returns number - not makes it 0, and if 0 it will return 1 */
	return !SortListSize( this);
}


sort_list_iter_ty SortListBegin(const sort_list_ty *this)
{
	sort_list_iter_ty curr_iter = {NULL};
	
	assert(this && "sort_list isn't valid");
	
	/* send this.dlist to DListBegin and updated the curr_iter.dlist_iter */
	ITER = DListBegin( DLIST);
			
	DEBUG_ONLY( curr_iter.this = ( sort_list_ty *)this; )
	
	return curr_iter;
}


sort_list_iter_ty SortListEnd( const sort_list_ty *this)
{
	sort_list_iter_ty curr_iter = {NULL};
	
	assert(this && "sort_list isn't valid");
	
	/* send this.dlist to DListEnd and updated the curr_iter.dlist_iter */
	ITER = DListEnd( DLIST);
	
	DEBUG_ONLY( curr_iter.this = ( sort_list_ty *)this; )
	
	return curr_iter;
}


sort_list_iter_ty SortListNext( sort_list_iter_ty curr_iter)
{	
	/* send curr_iter.dlist_iter to DListNext and updated it */
	ITER = DListNext( ITER);
	
	return curr_iter;
}


sort_list_iter_ty SortListPrev( sort_list_iter_ty curr_iter)
{
	/* send curr_iter.dlist_iter to DListPrev and updated it */
	ITER = DListPrev( ITER);
	
	return curr_iter;
}


int SortListIterIsEqual( sort_list_iter_ty iter1, sort_list_iter_ty iter2)
{	
	/* return 1 if they are equal, and 0 otherwise */
	return DListIsSameIter( iter1.dlist_iter, iter2.dlist_iter);
}



void *SortListGetData(sort_list_iter_ty curr_iter)
{	
	return DListGetData( ITER);
}



sort_list_iter_ty SortListInsert( sort_list_ty *this, const void *data)
{
	sort_list_iter_ty curr = { NULL};
	sort_list_iter_ty end = { NULL};
	
	assert( this && "sort_list isn't valid");
	
	/*assign curr_iter to the beginning of the list*/
	curr =  SortListBegin( this);
	end = SortListEnd( this);

	/* check if the list is empty or data is smaller than first item */
	if( SortListIsEmpty(this) ||  CMP( data, SortListGetData(curr)) < 0 )
	{
		/* insert the data to the beginning of the list  */
		curr.dlist_iter  = DListInsert( curr.dlist_iter ,data);
		
		return curr;
	}
	
	/* run untill list end or while user data smaller than current data*/
	while( FALSE == SortListIterIsEqual( curr, end) \
									&& CMP( SortListGetData( curr), data) < 0)
	{		
		curr =  SortListNext( curr);
	}
	
	/* insert the data before the corresponding item */
	curr.dlist_iter = DListInsert( curr.dlist_iter, data);
	
	return curr;
}
 

sort_list_iter_ty SortListRemove( sort_list_iter_ty curr_iter)
{	
	/* send curr_iter.dlist_iter to DListRemove and updated it */
	ITER = DListRemove( ITER);
	
	return curr_iter;
}


void *SortListPopFront( sort_list_ty *this)
{
	/* assert the list is valid */
	assert( this && "sort_list isn't valid");
	
	return DListPopFront( DLIST);
}


void *SortListPopBack( sort_list_ty *this)
{
	/* assert the list is valid */
	assert( this && "sort_list isn't valid");

	return DListPopBack( DLIST);
}


int SortListForEach( sort_list_iter_ty from, sort_list_iter_ty to,
					int ( *action_func)( void *data, const void *param),
					const void *param)
{	
	/* assert that the function pointer is valid */
	assert( action_func && "pointer to action function is not valid");
	
	/* test if to and from are from same list - debug only */
	DEBUG_ONLY( assert(to.this == from.this && "ptrs from different lists");) 
	
	return DListForEach(from.dlist_iter, to.dlist_iter, action_func, param);
}


sort_list_ty *SortListMerge( sort_list_ty *dest, sort_list_ty *src)
{
	/* define start and end iters of src list */
	sort_list_iter_ty src_iter = { NULL};
	sort_list_iter_ty src_end = { NULL};
	
	
	/* define start and end iters of dest list */
	sort_list_iter_ty dest_iter = { NULL};
	sort_list_iter_ty dest_end = { NULL};
	
	sort_list_iter_ty next = { NULL};
	
	assert( dest && "dest list isn't valid");
	assert( src && "src list isn't valid");
	assert( dest->cmp_func == src -> cmp_func && "different list types");
	
	/* initialise start and end iters of src list */
	src_iter = SortListBegin( src);
	src_end = SortListEnd( src);

	/* initialise start and end iters of dest list */
	dest_iter = SortListBegin( dest);
	dest_end = SortListEnd( dest);
	
	next = src_iter;
	
	/* test if dest is empty */
	if (SortListIsEmpty(dest))
    {
    	/* if it is - put whole src in dest and return dest */
        DListSplice(dest_iter.dlist_iter, src_iter.dlist_iter, src_end.dlist_iter);
        
        return dest;
    }
		
	/* run while you dont reach end of one of the lists */
	while(  !SortListIterIsEqual( dest_end, dest_iter) && \
										!SortListIterIsEqual( src_end, next))
	{	
		/* increment next ptr  you dont reach end of src or the compare function returns >0 */
		while( FALSE == SortListIterIsEqual( src_end, next) && \
		dest->cmp_func( SortListGetData(next) , SortListGetData(dest_iter) ) <0)
		{
			next = SortListNext( next);
		}
		
		/* extract all values from src that are smaller than current dest data
			and put them before this data in dest list, and update src iter*/		
		src_iter.dlist_iter = DListSplice(dest_iter.dlist_iter ,src_iter.dlist_iter ,next.dlist_iter);

		/* move to next dest iter */
		dest_iter = SortListNext(dest_iter);		
	}
	
	/*	insert all remaining src elements before the current dest */
	DListSplice( dest_iter.dlist_iter ,src_iter.dlist_iter ,src_end.dlist_iter);
	
	return dest;

} 



sort_list_iter_ty SortListFind(sort_list_ty *this, sort_list_iter_ty from, 
                               sort_list_iter_ty to, const void *data_to_find)
{
	/* assert the list pointer */
	assert(this && "sort_list isn't valid");
	
	/* test if to and from are from same list - debug only */
	DEBUG_ONLY( assert( to.this == from.this ); )
	
	/*return iterator to node returned by DListFind */
	return SortListFindIf(from, to, CMP , data_to_find);
}

                             


sort_list_iter_ty SortListFindIf(sort_list_iter_ty from, sort_list_iter_ty to, 
                                 int (*match_func)
                                 (const void *data, const void *param), 
                                 const void *param)
{
	sort_list_iter_ty curr_iter = {NULL};
	
	/* verify to and from are from same list - debug only */
	DEBUG_ONLY(assert(to.this == from.this && "pointers from different lists");) 

	/* use DListFind with user match_function */
	ITER = DListFind(from.dlist_iter, to.dlist_iter, match_func, param);
	
	DEBUG_ONLY( curr_iter.this = ( sort_list_ty *)from.this; )
	
	/*return iterator to node returned by DListFind */
	return curr_iter;
}



/**************** 			HELPER FUNCTIONS 	  	  *************************/

static sort_list_ty *InitSortlist(sort_list_ty *this, cmp_func_ty cmp_func)
{
	DLIST = DListCreate();
	
	/* test if malloc succeeded */
	MALLOC_TEST( DLIST == NULL , NULL, "alloc fail",  this,  NULL)
	
	CMP = cmp_func;
	
	return this;
}




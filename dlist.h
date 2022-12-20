/******************************************************************************
* Project: 	Doubly Linked List
* Author: 	Eli Feinshtein
* Date: 	27/10/2022
* Version:	1.0
*******************************************************************************/
#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /*size_t*/

#include "utils.h"

typedef struct dlist_node dlist_node_ty;

typedef struct dlist_iter dlist_iter_ty;

typedef struct dlist dlist_ty;


struct dlist_iter
{
	dlist_node_ty *dlist_node;
	
  
/*    DEBUG_ONLY(dlist_ty *dlist;)*/
};

/*action func return 0 on success and other on fail */
typedef int (*action_func_ty)(void *data, const void *param);
/*match func return 0 on success and other on fail*/
typedef int (*match_func_ty)(const void *data, const void *param);

/* Description: Creates a new doubly linked list.
   Arguments: 	void.
   Return: 		pointer to new double linked list or NULL on memory 
   				allocation fail.
   Complexity: 	O(1). 
   undefined behavior: none*/
dlist_ty *DListCreate(void);

/* Description: Frees a double linked list.
   Arguments: 	dlist_ty pointer pointing to list to be freed.
   Return: 		void
   Complexity: 	O(n). n num of element in the list
   undefined behavior: invalid pointer*/
void DListDestroy(dlist_ty *dlist_to_destroy);

/* Description: Count the number of element in the list.
   Arguments: 	dlist - pointer to the dlist to count.
   Return: 		num of element counted
   Complexity: 	O(n). n num of element
   undefined behavior: invalid pointer*/
size_t DListSize(const dlist_ty *dlist); 

/* Description: Checks if a list is empty.
   Arguments: 	dlist - pointer to the dlist to check.
   Return: 		1 if empty 0 if not
   Complexity: 	O(1). 
   undefined behavior: invalid pointer*/
int DListIsEmpty(const dlist_ty *dlist); 
 
/* Description: Returns an iterator to the first valid node in the dlist 
				or the end DUMMY in case of an empty list.
   Arguments:	dlist - pointer to the dlist
   Return: 		iterator to the first valid node of dlist.
   Complexity : O(1)
   Undefine behavior : Invalid list.*/
dlist_iter_ty DListBegin(const dlist_ty *dlist);

/* Description: Returns an iterator to the end of the list (end DUMMY).
   Arguments:	dlist - pointer to the dlist
   Return: 		iterator to the last node (end DUMMY).
   Complexity:  O(1)
   Undefine behavior: Invalid list.*/
dlist_iter_ty DListEnd(const dlist_ty *dlist);

/* Description: Returns an iterator of the following node in the dlist.
   Arguments: 	curr_iter - current iterator .
   Return: 		iterator of next node.
   Complexity : O(1)
   Undefine behavior : Invalid iterator or iterator to end DUMMY*/ 
dlist_iter_ty DListNext(const dlist_iter_ty curr_iter);

/* Description: Returns an iterator of the previous node in the dlist.
   Arguments:	curr_iter - current iterator.
   Return: 		iterator to previous node.
   Complexity:  O(1)
   Undefine behavior: Invalid iterator or iterator to head DUMMY*/
dlist_iter_ty DListPrev(const dlist_iter_ty curr_iter);

/* Description: Retrieve data from a node.
   Arguments: 	curr_iter - current iterator.
   Return: 		the data stored at the node by reference.
   Complexity: 	O(1).
   undefined behavior: invalid iterator*/
void *DListGetData(const dlist_iter_ty curr_iter);

/* Description: compare two iterator and check if they point to the same node.
   Arguments: 	iter1 iter to the first node.
   				iter2 iter to the second node
   Return: 		1 if equal, 0 if not
   Complexity: 	O(1).
   undefined behavior: invalid iterators*/
int DListIsSameIter(const dlist_iter_ty iter1, const dlist_iter_ty iter2);

/* Description: Insert a new node before the curr_iter.
   Arguments: 	curr_iter - current iterator.
				data- data to be set in the node
   Return: 		Iterator to the new_node or DUMMY end incase of memory 
   				allocation fail
   Complexity: 	O(1) on success, incase of failure o(n), n is num of element 
   				from curr_iter to DUMMY.
   undefined behavior: invalid iterator*/
dlist_iter_ty DListInsert(dlist_iter_ty curr_iter, const void *data);

/* Description: Remove a single node in the dlist.
   Arguments: 	node_to_remove - pointing to the node that will be removed.
   Return: 		Iterator to the next node 
   Complexity: 	O(1).
   undefined behavior: invalid iterator trying to remove end DUMMY*/
dlist_iter_ty DListRemove(dlist_iter_ty node_to_remove);

/* Description: push a new node to front of the dlist 
   Arguments: 	dlist - pointer to the dlist 
   				data  - the data to be set in the node
   Return: 		Iterator to the new_node or DUMMY end if memory allocation fail
   Complexity: 	O(1).
   undefined behavior: invalid pointer*/
dlist_iter_ty DListPushFront(dlist_ty *dlist, const void *data);

/* Description: push a new node to end of the dlist 
   Arguments: 	dlist - pointer to the dlist 
   				data  - the data to be set in the node
   Return: 		Iterator to the new_node or DUMMY end if memory allocation fail
   Complexity: 	O(1).
   undefined behavior: invalid pointer*/
dlist_iter_ty DListPushBack(dlist_ty *dlist, const void *data);

/* Description: remove the first node of the dlist
   Arguments: 	dlist - pointer to the dlist
   Return: 		the data from the popped node
   Complexity: 	O(1).
   undefined behavior: invalid pointer trying to remove from an empty list*/
void *DListPopFront(dlist_ty *dlist);

/* Description: remove the last node of the dlist
   Arguments: 	dlist - pointer to the dlist
   Return: 		the data from the popped node
   Complexity: 	O(1).
   undefined behavior: invalid pointer trying to remove from an empty list*/
void *DListPopBack(dlist_ty *dlist);

/* Description: Call for 'action_func' on the nodes data within a specified
				range using param.
  				If the action_func return non 0 value, DListForEach returns. 
   Arguments: 	from - iterator object indicating range start (including 'from')
   				to - iterator object indicating range end (excluding 'to').
                action_func_ty - Pointer to action function.
				param - Data to act with.
   Return: 		On success 0 else otherwise.
   Complexity: 	O(n) n is number of nodes from 'from' to 'to'.
   undefined behavior: invalid iterator. to and from are part of diffrent lists.
   					   'to' is before 'from'*/
int DListForEach(dlist_iter_ty from, dlist_iter_ty to,
				  action_func_ty action_func, const void *param);

/* Description: Splice the semi list indicated by the range 'from' to 'to',
 				to the location pointed by iterator 'where'.
   Arguments: 	where - the location at which to splice 
   				from - iterator object indicating range start (including 'from')
   				to - iterator object indicating range end (excluding 'to').
   Return: 		An iterator to the end of the spliced element
   Complexity: 	O(1).
   undefined behavior: invalid iterator, all iter are not from the same list,
   			 from is ahead of to*/
dlist_iter_ty DListSplice(dlist_iter_ty where, dlist_iter_ty from,
						  dlist_iter_ty to);

/* Description: Finds the first node thet matchs the condition definded by
				'match_func' within a specified range. 
   Arguments: 	from - iterator object indicating range start (including 'from')
   				to - iterator object indicating range end (excluding 'to').
                match_func - pointer to user implemented matching func.
                param - used by 'match_func' to perform the condition 
   Return: 		Iterator to the first matched node. or DUMMY end incase of non
   				matched node.
   Complexity: 	O(n). n is number of nodes from 'from' to 'to' 
   Undefined behavior: Invalid iterator, to and from are from diffrent list
   note:		match_function should returns 0 if a match is found.
   			 	else, if not a match*/
dlist_iter_ty DListFind(dlist_iter_ty from, dlist_iter_ty to,
						match_func_ty match_func, const void *param);

/* Description: Finds all nodes thet matchs the condition definded by 
				match_func' within a specified range. for every match a node
				with the matched data is added to 'output_list'.
   Arguments: 	from - iterator object indicating range start (including 'from')
   				to - iterator object indicating range end (excluding 'to').
                match_func - pointer to user implemented matching func
                param - used by 'match_func' to perform the condition 
                to match.
                output_list - a pointer to container list for the matched data. 
   Return:	 	num of found elements on success, -1 on memory allocation fail.
   Complexity: 	O(n). n is number of nodes from 'from' to 'to' 
   Undefined behavior:  Invalid iterator, to and from are from diffrent list
   note:		match_function should returns 0 if a match is found else if not
   				a match*/
int DListMultiFind(dlist_iter_ty from, dlist_iter_ty to,
				   match_func_ty match_func, const void *param,
				    dlist_ty *output_list);




#endif /*__DLIST_H__*/

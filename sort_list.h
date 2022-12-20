/******************************************************************************
 Project: 	Sorted Linked List
 Author: 	Eli Feinshtein
 Date: 		31/10/22
 Version:	1.0
*******************************************************************************/
#ifndef __SORT_LIST_H__
#define __SORT_LIST_H__

#include <stddef.h> /*size_t*/

#include "dlist.h" 
#include "utils.h"

typedef struct sort_list sort_list_ty;
typedef struct sort_list_iter sort_list_iter_ty;

/*return == 0 if data1 equal data2,  return < 0 if data1 lower then data2, 
return > 0 if data1 higher then data2*/
typedef int (*cmp_func_ty)(const void *data1, const void *data2); 

struct sort_list_iter
{
	dlist_iter_ty dlist_iter;
  
 	DEBUG_ONLY(sort_list_ty *this;)
};

/* Description: Creates a new sorted linked list.
   Arguments:	cmp_func - user function of sorting condition
   Return: 		Pointer to new sorted linked list or NULL on memory 
   				allocation fail.
   Complexity: 	O(1). 
   Undefined behavior: none*/
sort_list_ty *SortListCreate(cmp_func_ty cmp_func);

/* Description: Frees a sorted linked list.
   Arguments: 	sort_list_ty pointer pointing to list to be freed.
   Return: 		void
   Complexity: 	O(n). n num of elements in the list
   Undefined behavior: 	Invalid pointer*/
void SortListDestroy(sort_list_ty *this);

/* Description: Return the size of a sorted list.
   Arguments: 	sorted list pointer.
   Return: 		number of valid elements in the list.
   Complexity: 	O(n). 
   Undefined behavior: Invalid pointer*/
size_t SortListSize(const sort_list_ty *this);

/* Description: Checks if a list is empty.
   Arguments: 	sorted list pointer.
   Return: 		1 if list is empty, 0 otherwise..
   Complexity: 	O(1). 
   Undefined behavior: Invalid pointer*/
int SortListIsEmpty(const sort_list_ty *this);

/* Description: Returns an iterator to the first valid node in the sorted list 
				or the end DUMMY in case of an empty list.
   Arguments:	pointer to the sorted list
   Return: 		Iterator to the first valid node of sorted list.
   Complexity : O(1)
   Undefine behavior : 	Invalid list.*/
sort_list_iter_ty SortListBegin(const sort_list_ty *this);

/* Description: Returns an iterator to the end of the list (end DUMMY).
   Arguments:	pointer to the sorted list
   Return: 		Iterator to the last node (end DUMMY).
   Complexity:  O(1)
   Undefine behavior: 	Invalid list.*/
sort_list_iter_ty SortListEnd(const sort_list_ty *this);

/* Description: Returns an iterator of the following node in the sorted list.
   Arguments: 	curr_iter - current iterator .
   Return: 		Iterator of next node.
   Complexity : O(1)
   Undefine behavior : 	Invalid iterator or iterator to end DUMMY*/ 
sort_list_iter_ty SortListNext(sort_list_iter_ty curr_iter);

/* Description: Returns an iterator of the previous node in the sorted list.
   Arguments:	curr_iter - current iterator.
   Return: 		iterator to previous node.
   Complexity:  O(1)
   Undefine behavior: Invalid iterator or iterator to head DUMMY*/
sort_list_iter_ty SortListPrev(sort_list_iter_ty curr_iter);

/* Description: compare two iterator and check if they point to the same node.
   Arguments: 	iter1 iterator to the first node.
   				iter2 iterator to the second node
   Return: 		1 if equal, 0 if not
   Complexity: 	O(1).
   Undefined behavior: 	Invalid iterators*/
int SortListIterIsEqual(sort_list_iter_ty iter1, sort_list_iter_ty iter2);

/* Description: Retrieve data from a node.
   Arguments: 	curr_iter - current iterator.
   Return: 		The data stored at the node by reference.
   Complexity: 	O(1).
   Undefined behavior: 	Invalid iterator*/
void *SortListGetData(sort_list_iter_ty curr_iter);

/* Description: Insert a new node in sorted way according to user sorting 
				conditions.
   Arguments: 	pointer to the sorted list.
				data to be set in the node.
   Return: 		Iterator to the new_node or DUMMY end incase of memory 
   				allocation fail
   Complexity: 	O(n) n is num of element.
   Undefined behavior: 	Invalid pointer*/
sort_list_iter_ty SortListInsert(sort_list_ty *this, const void *data);
 
/* Description: Remove a single node in the sorted list.
   Arguments: 	iter_to_remove - pointing to the node that will be removed.
   Return: 		Iterator to the next node 
   Complexity: 	O(1).
   Undefined behavior: 	Invalid iterator ,trying to remove end or head DUMMY*/
sort_list_iter_ty SortListRemove(sort_list_iter_ty iter_to_remove);

/* Description: remove the first node of the sorted list
   Arguments: 	this - pointer to the sorted list
   Return: 		The data from the popped node
   Complexity: 	O(1).
   Undefined behavior: 	Invalid pointer, trying to remove from an empty list*/
void *SortListPopFront(sort_list_ty *this);

/* Description: remove the last node of the sorted list
   Arguments: 	pointer to the sorted
   Return: 		The data from the popped node
   Complexity: 	O(1).
   Undefined behavior:	Invalid pointer, trying to remove from an empty list*/
void *SortListPopBack(sort_list_ty *this);

/* Description: Call for 'action_func' on the nodes data within a specified
				range using param.
  				If the action_func return non 0 value, SortListForEach returns. 
   Arguments: 	from - iterator object indicating range start (including 'from')
   				to - iterator object indicating range end (excluding 'to').
                Pointer to action function.
				param - parameter to act with.
   Return:	 	 0 on success else otherwise.
   Complexity: 	O(n) n is number of nodes from 'from' to 'to'.
   Undefined behavior: 	Invalid iterator. to and from are part of diffrent lists.
   				to' is before 'from'*/
int SortListForEach(sort_list_iter_ty from, sort_list_iter_ty to,
					int (*action_func)(void *data, const void *param),
					const void *param);

/* Description: Merge src sorted list to dest in a sorted way, leaving src 
				empty. src and dest must have the same sorting conditions
				(the same 'cmp_func').
   Arguments: 	dest - pointer to dest sorted list.
   				src - pointer to src sorted list.
   Return: 		pointer to dest sorted list.
   Complexity: 	O(n+m). n is number of nodes in dest m is number of nodes in src.
   Undefined behavior: Invalid pointers*/
sort_list_ty *SortListMerge(sort_list_ty *dest, sort_list_ty *src); 

/* Description: Finds the first node thet matchs the data to find by the comapre
				function given, within a specific range. 
   Arguments: 	pointer to sorted list.
   				from - iterator object indicating range start (including 'from')
   				to - iterator object indicating range end (excluding 'to').
                data_to_find 
   Return: 		Iterator to the first founed node. or DUMMY end incase of non
   				founed node.
   Complexity: 	O(n). n is number of nodes from 'from' to 'to' 
   Undefined behavior: Invlaid pointer, invalid iterator, to and from are from 
   					   diffrent list*/
sort_list_iter_ty SortListFind(sort_list_ty *this, sort_list_iter_ty from, 
                               sort_list_iter_ty to, const void *data_to_find);
                               
/* Description: Finds the first node thet matchs the condition definded by
				'match_func' within a specified range. 
	given the data and the parameter
   Arguments: 	pointer to sorted list.
   				from - iterator object indicating range start (including 'from').
   				to - iterator object indicating range end (excluding 'to').
                match_func - pointer to user implemented matching func.
                param - used by 'match_func' to perform the condition  
   Return: 		Iterator to the first matched node. or DUMMY end incase of non
   				matched node.
   Complexity: 	O(n). n is number of nodes from 'from' to 'to' 
   Undefined behavior: Invlaid pointer, invalid iterator, to and from are from 
   					   diffrent list
   note:		match_function should returns 0 if a match is found.
   			 	  else, if not a match*/
sort_list_iter_ty SortListFindIf(sort_list_iter_ty from, sort_list_iter_ty to, 
                                 int (*match_func)
                                 (const void *data, const void *param), 
                                 const void *param);

#endif /* __SORT_LIST_H__*/

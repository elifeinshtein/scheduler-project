/******************************************************************************
* Project : Doubly Linked List
* Author : Eli Feinshtein
* Date : 27/10/2022
* Version : 1.0
*******************************************************************************/

#include <stdio.h>  /* printf */
#include <string.h> /* strcpy , strcmp*/
#include <stdlib.h> /* malloc ,free*/

#include "dlist.h"
#include "test_utils.h"

/****************************       FORWARD DECLARATIONS		***************/
void DlistTestFunc();
int AddParam(void *data, const void *param);
int MatchParam(const void *data,const void *param);
int LargerThan(const void *data,const void *param);
void PrintList(dlist_ty *dlist);



int main() 
{
	UNUSED(success_counter_g);
	UNUSED(test_counter_g);
	DlistTestFunc();
				
	return 0;	
}

void DlistTestFunc()
{
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;
	int element5 = 5;
	int tester =0, counter =0;
	size_t count = 0;

/*	int previous_element = 0;*/
	int param = 3;
	
	dlist_iter_ty start, end, next, test;
	
	action_func_ty add_param_ptr = AddParam;
	match_func_ty match_param_ptr = MatchParam;
	match_func_ty match_param_ptr2 = LargerThan;
	
	dlist_ty *my_dlist = NULL;
	dlist_ty *multi_dlist = NULL;
	
	my_dlist = DListCreate();
	
	start = DListBegin(my_dlist);

	/**************				INSERT TESTS		 				**********/
	
	printf("%-33s:","INSERT BEGIN + GET TEST");	
	
	DListInsert( start, &element1);	

	element2 - *(int*)DListGetData( DListInsert( start, &element2) ) ?FAIL:PASS;

	printf("%-33s:","INSERT END + GET TEST");	
	
	end = DListEnd( my_dlist);	

	element3 - *(int*)DListGetData( DListInsert( end, &element3) ) ? FAIL:PASS ;

	printf("%-33s:","INSERT NEXT + GET TEST");

	next = DListNext( DListBegin(my_dlist));

	element1 - *(int*)DListGetData( DListInsert( next, &element1) ) ? FAIL:PASS;
	
	printf("%-33s:","PREV + GET TEST");
	
	test = DListPrev( DListEnd(my_dlist));
	test = DListPrev( test);
	
	element2 - *(int*)DListGetData( test ) ? FAIL:PASS;


	/**************		COUNT AND ISSAME TEST		 				***********/
	
	printf("%-33s:","COUNT AND ISSAME TEST");	
	
	start = DListBegin(my_dlist); 
	end = DListEnd(my_dlist);
	
	while ( !DListIsSameIter( end ,DListNext(start) ) )
	{
		++count;
		start = DListNext(start);
	}
	++count;
	
	DListSize(my_dlist) - count ? FAIL:PASS;
	
	
	/**************					REMOVE TEST		 				***********/
	
	printf("%-33s:","REMOVE TEST");	
		
	start = DListBegin(my_dlist); 
	next = DListNext(start);	
	count = DListSize(my_dlist);

	next = DListRemove(next); /* USING THE REMOVE FUNCTIN */

	count - DListSize(my_dlist) == 1 && \
					element2 - *(int*)DListGetData( next ) == 0 ? PASS : FAIL ;
	

	/**************				PUSH BACK TEST		 				***********/
	
	printf("%-33s:","PUSH BACK TEST");	
	
	count = DListSize(my_dlist);
	
	DListPushBack(my_dlist, &element4);
	
	end = DListEnd(my_dlist);
	
	DListSize(my_dlist) - count == 1 && \
	element4 - *(int*)DListGetData( DListPrev(end) ) == 0 && \
	element3 - *(int*)DListGetData( DListPrev(DListPrev(end))) == 0? PASS :FAIL;


	/**************				PUSH FORNT TEST		 				***********/
	
	printf("%-33s:","PUSH FRONT TEST");	
	
	count = DListSize(my_dlist);
	
	DListPushFront(my_dlist, &element4);
	
	DListSize(my_dlist) - count == 1 && \
	element4 - *(int*)DListGetData( DListBegin(my_dlist) ) == 0 ? PASS : FAIL;


	/**************				POP FRONT TEST		 				***********/
	
	printf("%-33s:","POP FRONT TEST");	
	
	count = DListSize(my_dlist);
	
	element4 - *(int*)DListPopFront( my_dlist ) == 0 && \
								count - DListSize(my_dlist) == 1 ? PASS : FAIL;
	
	
	/**************				POP BACK TEST		 				***********/
	
	printf("%-33s:","POP BACK TEST");	
	
	count = DListSize(my_dlist);
	
	element4 - *(int*)DListPopBack( my_dlist ) == 0 && \
								count - DListSize(my_dlist) == 1 ? PASS : FAIL;
								
	
	/******************           ForEach TEST   		  *********************/	
	
	printf("%-33s:","FOR EACH TEST");

	start = DListBegin(my_dlist); 
	next = DListNext(start);
	tester = *(int*)DListGetData( start );
	
	DListForEach( start, next , add_param_ptr, &param);

	*(int*)DListGetData( start ) - tester- param == 0 ? PASS : FAIL ;
	
	
	/******************           MATCH TEST 		  	  *********************/	
	
	printf("%-33s:","MATCH TEST");

	start = DListBegin(my_dlist); 
	end = DListEnd(my_dlist);
	param = 3;
	
	test = DListFind( start, end , match_param_ptr, &param);

	*(int*)DListGetData( test ) - element3 == 0 ? PASS : FAIL ;
	
	
	/******************         MULTI MATCH TEST 		  *********************/	
	
	printf("%-33s:","MULTI MATCH TEST");
	
	element1 = 1;
	
	DListPushFront(my_dlist, &element2);
	DListPushBack(my_dlist, &element4);
	DListPushFront(my_dlist, &element5);
	param = 2;
	multi_dlist =  DListCreate();
	
	start = DListBegin(my_dlist); 
	end = DListEnd(my_dlist);
					
	tester = DListMultiFind( start, end , match_param_ptr2, &param, multi_dlist);
	
	start = DListBegin(multi_dlist); 
	end = DListEnd(multi_dlist);
	
	while ( !DListIsSameIter( end , start) )
	{
		counter += !LargerThan( DListGetData(start), &param ) ;
		start = DListNext(start);
	}	
	
	counter == tester ? PASS : FAIL ;
		
	/******************         SPLICE TEST 		  *********************/	
	
	printf("%-33s:","SPLICE TEST");
	
	DListDestroy( multi_dlist );
	multi_dlist =  DListCreate();
	 
	start = DListNext( DListBegin( my_dlist));

	end = DListPrev( DListPrev( DListEnd( my_dlist)));
	count = DListSize( my_dlist);
PrintList(my_dlist);
	DListSplice( DListBegin( my_dlist), start, start);
PrintList(my_dlist);
	count - DListSize( my_dlist) - DListSize( multi_dlist) == 0 && \
	*(int*)DListGetData( DListBegin(multi_dlist)) - element2 == 0 ? PASS : FAIL;

/*	PrintList(my_dlist);*/

	DListDestroy( my_dlist );
	DListDestroy( multi_dlist );
}


int MatchParam(const void *data, const void *param)
{
	return *(int*)data == *(int*)param ? 0 : 1 ;
}


int LargerThan(const void *data, const void *param)
{
	return *(int*)data > *(int*)param ? 0 : 1 ;
}

int AddParam(void *data, const void *param)
{
	*(int*)data += *(int*)param;	
	
	return *(int*)data;
}

void PrintList(dlist_ty *dlist)
{
	dlist_iter_ty start, end;
	
	start = DListBegin(dlist); 
	end = DListEnd(dlist);
	
	printf("\n---list--\n");
	
	while ( !DListIsSameIter( end ,start ) )
	{
		printf("%d\n",*(int*)DListGetData(start));
		start = DListNext(start);
	}
	
}



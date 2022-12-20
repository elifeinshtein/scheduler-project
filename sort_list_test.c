/******************************************************************************
* Project : Sorted  List
* Author : Eli Feinshtein
* Date : 1/11/22
* Version : 1.0
*******************************************************************************/

#include <stdio.h>  /* printf */
#include <string.h> /* strcpy , strcmp*/
#include <stdlib.h> /* malloc ,free*/

#include "sort_list.h"
#include "test_utils.h"

/*******************	 GLOBAL VARIABLES FOR TEST 			*******************/	

int element1 = 18;
int element2 = 5;
int element3 = -3;
int element4 = 150;
int element5 = -5;

int l2elem1 = -15;
int l2elem2 = 148;
int l2elem3 = 23;
int l2elem4 = -9;

char string1[] = "home";
char string2[] = "zoo";
char string3[] = "horse";
char string4[] = "astronaut";
char string5[] = "fox";	
	
int tester = 0;

size_t count = 0;

int param = 3;
	
/****************************       FORWARD DECLARATIONS		***************/
/* test functions */
void MergeTest();
void InsertTest();
void IsemptyTest();
void IsequalSizeNext();
void RemoveAndPopTest();
void FindTests();
void ForEachTeast();

void ListInit(sort_list_ty *sort_list, int var);

/* user functions */
int AddParam(void *data, const void *param);
int MatchParam(const void *data,const void *param);
int NumCompare(const void *data1, const void *data2); 
int WordCompare(const void *data1, const void *data2);

/* printer functions */
void PrintList(sort_list_ty *sort_list);
void PrintStringList(sort_list_ty *sort_list);


/**************************         MAIN            ***************************/

int main() 
{
	IsemptyTest();
	InsertTest();
	IsequalSizeNext();
	RemoveAndPopTest();
	FindTests();
	ForEachTeast();
	MergeTest();
	(void)success_counter_g;
	(void)test_counter_g;				
	return 0;	
}



void InsertTest()
{
	sort_list_ty *sort_list = NULL;
	sort_list_ty *sort_list2 = NULL;

	cmp_func_ty cmp_func_ptr = NumCompare;
	cmp_func_ty cmp_func_ptr2 = WordCompare;
	
	sort_list = SortListCreate(cmp_func_ptr);
	sort_list2 = SortListCreate(cmp_func_ptr2);
	
	printf("%-33s:","INSERT + END + PREV + GET TEST");	
	
	/* initialise the lists */
	ListInit(sort_list,1);
	ListInit(sort_list2,2);
	
	memcmp( &element4, SortListGetData( SortListPrev( SortListEnd( sort_list))), sizeof(int)) == 0 && \
	memcmp( &string2, SortListGetData( SortListPrev(SortListEnd( sort_list2))), sizeof(string2)) == 0 ?
	PASS : FAIL ;

	printf("%-33s:","INSERT + BEGIN + GET TEST");	
	
	SortListInsert( sort_list, &element4);
	SortListInsert( sort_list, &element5);
	
	SortListInsert( sort_list2, string4);
	SortListInsert( sort_list2, string5);
	
	memcmp( &element5, SortListGetData( SortListBegin( sort_list)), sizeof(int)) == 0 && \
	memcmp( &string4, SortListGetData( SortListBegin( sort_list2)), sizeof(string4)) == 0 ?
	PASS : FAIL ;
	
	printf("%-33s:","INSERT + BEGIN + NEXT + GET TEST");	
	
	memcmp( &element5, SortListGetData( SortListNext(SortListBegin( sort_list))), sizeof(int)) == 0 && \
	memcmp( &string4, SortListGetData( SortListNext(SortListBegin( sort_list2))), sizeof(string4)) == 0 ?
	PASS : FAIL ;
	
	SortListDestroy( sort_list );
	SortListDestroy( sort_list2 );
}



void IsemptyTest()
{
	sort_list_ty *sort_list = NULL;

	cmp_func_ty cmp_func_ptr = NumCompare;
	
	sort_list = SortListCreate(cmp_func_ptr);
	
	printf("%-33s:","ISEMPTY TEST");	
		
	SortListIsEmpty(sort_list) ? PASS : FAIL ;
	
	SortListDestroy( sort_list );
}



void IsequalSizeNext()
{
	sort_list_ty *sort_list2 = NULL;
	sort_list_ty *sort_list = NULL;
	
	sort_list_iter_ty start, end;

	cmp_func_ty cmp_func_ptr = WordCompare;
	
	sort_list2 = SortListCreate(cmp_func_ptr);
	sort_list = SortListCreate(cmp_func_ptr);
	
	ListInit(sort_list,1);
	ListInit(sort_list2,2);
	
	printf("%-33s:","ISEQUAL + SIZE + NEXT TEST");	
		
	start = SortListBegin(sort_list2); 
	end = SortListEnd(sort_list2);
	
	while ( !SortListIterIsEqual( end ,start ))
	{
		++count;
		start = SortListNext(start);
	}

	count - 5 &&							\
	SortListSize(sort_list2) - count &&		\
	SortListSize(sort_list) - SortListSize(sort_list2) == 0 ? FAIL : PASS;
	
	SortListDestroy( sort_list2 );
	SortListDestroy( sort_list );
}



void RemoveAndPopTest()
{
	sort_list_iter_ty start, next;

	cmp_func_ty cmp_func_ptr = NumCompare;
	cmp_func_ty cmp_func_ptr2 = WordCompare;
	
	sort_list_ty *sort_list = NULL;
	sort_list_ty *sort_list2 = NULL;
	
	sort_list = SortListCreate(cmp_func_ptr);
	sort_list2 = SortListCreate(cmp_func_ptr2);	
	
	/* initialise the lists */
	ListInit(sort_list,1);
	ListInit(sort_list2,2);
	

	printf("%-33s:","REMOVE TEST");	
		
	start = SortListBegin(sort_list2);
	next = SortListNext(start);	
	count = SortListSize(sort_list2);

	next = SortListRemove(next); 

	count - SortListSize(sort_list2) == 1 && \
	memcmp( string1 ,SortListGetData( next ), sizeof(string1)) == 0 ? PASS :FAIL;
	

	
	printf("%-33s:","POP FRONT TEST");	
	
	count = SortListSize(sort_list);

	element5 - *(int*)SortListPopFront( sort_list ) == 0 && \
							count - SortListSize(sort_list) == 1 ? PASS : FAIL;
	

	
	printf("%-33s:","POP BACK TEST");	
	
	count = SortListSize(sort_list2);

	memcmp( string2 ,SortListPopBack( sort_list2 ) , sizeof(string2)) == 0 && \
							count - SortListSize(sort_list2) == 1 ? PASS : FAIL;
							
	SortListDestroy( sort_list );
	SortListDestroy( sort_list2 );
}

void FindTests()
{
	sort_list_iter_ty start, end, curr;
	
	match_func_ty match_param_ptr = MatchParam;
	
	cmp_func_ty cmp_func_ptr = NumCompare;
	
	sort_list_ty *sort_list = NULL;

	sort_list = SortListCreate(cmp_func_ptr);

	/* initialise the list */
	ListInit(sort_list,1);
	
	printf("%-33s:","FIND TEST");
	
	start = SortListBegin(sort_list); 
	end = SortListEnd(sort_list);
	tester = 15;

	curr = SortListFind( sort_list, start, end, &tester);
	start = SortListFind( sort_list, start, end, &element3);
	
	SortListIterIsEqual( curr, end)  && \
	*(int*)SortListGetData( start) - element3 == 0 ? PASS : FAIL;

	
	printf("%-33s:","FIND IF TEST");
	
	start = SortListBegin(sort_list); 
	end = SortListEnd(sort_list);
	
	tester = 18;
	
	curr = SortListFindIf(start, end, match_param_ptr , &tester);

	*(int*)SortListGetData( curr) - tester == 0  ? PASS : FAIL;
	
	SortListDestroy( sort_list );
}

void ForEachTeast()
{
	sort_list_iter_ty start, end, next;
	
	action_func_ty add_param_ptr = AddParam;
	
	cmp_func_ty cmp_func_ptr = NumCompare;
	
	sort_list_ty *sort_list = NULL;
	
	sort_list = SortListCreate(cmp_func_ptr);
	
	/* initialise the lists */
	ListInit(sort_list,1);
	
	printf("%-33s:","FOR EACH TEST");

	start = SortListBegin(sort_list); 
	end = SortListEnd(sort_list);
	next = SortListNext(start);
	
	tester = *(int*)SortListGetData( next);
	
	SortListForEach( start, end , add_param_ptr, &param);

	*(int*)SortListGetData( next) - tester - param == 0 ? PASS : FAIL ;
	
	SortListDestroy( sort_list );
}

void MergeTest()
{	
	sort_list_iter_ty end, curr;
	
	cmp_func_ty cmp_func_ptr = NumCompare;
	
	sort_list_ty *sort_list = NULL;
	sort_list_ty *sort_list3 = NULL;
	sort_list_ty *sort_list2 = NULL;
	
	sort_list = SortListCreate(cmp_func_ptr);
	sort_list2 = SortListCreate(cmp_func_ptr);
	sort_list3 = SortListCreate(cmp_func_ptr);
	
	/* initialise the lists */
	ListInit(sort_list,1);
	ListInit(sort_list3,3);

	printf("%-33s:","MERGE TEST");
	
	SortListDestroy( sort_list );
	sort_list = SortListCreate(cmp_func_ptr);
	
	/* initialise the lists */
	ListInit(sort_list,1);
	ListInit(sort_list3,3);
	
	SortListMerge(sort_list, sort_list3);
	SortListMerge(sort_list2, sort_list3);
	
	curr = SortListNext( SortListBegin(sort_list)); 
	end = SortListEnd(sort_list);
	count = 0;
	
	while ( !SortListIterIsEqual( end ,curr ) && NumCompare( SortListGetData(SortListPrev(curr)) , SortListGetData(curr) ) <= 0 ) 
	{	
		curr = SortListNext(curr);
		++count;
	}	
	
	++count;
	
	SortListSize(sort_list) - count == 0 && \
	SortListSize(sort_list2) == SortListSize(sort_list3) ? PASS : FAIL;

/*	PrintStringList(sort_list2);*/
/*	PrintList(sort_list);*/

	SortListDestroy( sort_list );
	SortListDestroy( sort_list2 );
	SortListDestroy( sort_list3 );

}

/*************************** 		helper funcs 		***********************/

void ListInit(sort_list_ty *sort_list, int var)
{
	if (1 == var)
	{
		SortListInsert( sort_list, &element1);	
		SortListInsert( sort_list, &element2);	
		SortListInsert( sort_list, &element3);
		SortListInsert( sort_list, &element4);
		SortListInsert( sort_list, &element5);	
	}
	
	if (2 == var)
	{
		SortListInsert( sort_list, &string1);	
		SortListInsert( sort_list, &string2);	
		SortListInsert( sort_list, &string3);
		SortListInsert( sort_list, &string4);
		SortListInsert( sort_list, &string5);	
	}
	
	if (3 == var)
	{
		SortListInsert( sort_list, &l2elem1);	
		SortListInsert( sort_list, &l2elem2);	
		SortListInsert( sort_list, &l2elem3);
		SortListInsert( sort_list, &l2elem4);
	}
}


void PrintList(sort_list_ty *sort_list)
{
	sort_list_iter_ty start, end;
	
	start = SortListBegin(sort_list); 
	end = SortListEnd(sort_list);
	
	printf("\n---list--\n");
	
	while ( !SortListIterIsEqual( end ,start ) )
	{
		printf("%d\n",*(int*)SortListGetData(start));
		start = SortListNext(start);
	}
	
}

void PrintStringList(sort_list_ty *sort_list)
{
	sort_list_iter_ty start, end;
	
	start = SortListBegin(sort_list); 
	end = SortListEnd(sort_list);
	
	printf("\n---list--\n");
	
	while ( !SortListIterIsEqual( end ,start ) )
	{
		printf("%s\n",(char*)SortListGetData(start));
		start = SortListNext(start);
	}
	
}

/****************************		user funcs	******************************/

int MatchParam(const void *data, const void *param)
{
	return *(int*)data == *(int*)param ? 0 : 1 ;
}


int NumCompare(const void *data1, const void *data2)
{
	
	if(*(int*)data1 == *(int*)data2)
	{
		return 0;
	}
	
	return *(int*)data1 < *(int*)data2 ? -1 : 1 ;
}



int WordCompare(const void *data1, const void *data2)
{
	
	if( 0 == strcmp((char*)data1, (char*)data2 ) )
	{
		return 0;
	}
	
	return strcmp((char*)data1, (char*)data2 ) > 0 ? 1 : -1 ;
}



int AddParam(void *data, const void *param)
{
	*(int*)data += *(int*)param;	
	
	return 0;
}





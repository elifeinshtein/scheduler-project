/******************************************************************************
* Project : Priority queue
* Author: 	Eli Feinshtein	
* Date: 	3/11/22
* Version:	1.0
*******************************************************************************/

#include <stdio.h>  /* printf */
#include <string.h> /* strcpy , strcmp*/
#include <stdlib.h> /* malloc ,free*/

#include "p_queue.h"
#include "test_utils.h"

/*******************	 GLOBAL VARIABLES FOR TEST 			*******************/	

int element1 = 18;
int element2 = 5;
int element3 = -3;
int element4 = 150;
int element5 = -5;

char string1[] = "home";
char string2[] = "zoo";
char string3[] = "horse";
char string4[] = "astronaut";
char string5[] = "fox";	

	
/****************************       FORWARD DECLARATIONS		***************/
/* test functions */

void InsertTest();
void IsemptyTest();
void PeekTest();
void SizeTest();
void ClearTests();
void EraseTest();

void ListInit(p_que_ty *p_que, int var);

/* user functions */
int AddParam(void *data, const void *param);
int MatchParam(const void *data,const void *param);
int NumCompare(const void *data1, const void *data2); 
int WordCompare(const void *data1, const void *data2);


/**************************         MAIN            ***************************/



int main() 
{

	(void)success_counter_g;
	(void)test_counter_g;
	IsemptyTest();
	InsertTest();
	PeekTest();
	SizeTest();
	ClearTests();
	EraseTest();
				
	return 0;	
}

void IsemptyTest()
{
	p_que_ty *p_que = NULL;

	cmp_func_ty cmp_func_ptr = NumCompare;
	
	p_que = PQueueCreate(cmp_func_ptr);
	
	printf("%-33s:","ISEMPTY TEST");	
		
	PQueueIsEmpty( p_que) ? PASS : FAIL ;
	
	PQueueDestroy( p_que );
}


void InsertTest()
{
	p_que_ty *p_que = NULL;
	p_que_ty *p_que2 = NULL;

	cmp_func_ty cmp_func_ptr = NumCompare;
	cmp_func_ty cmp_func_ptr2 = WordCompare;
	
	p_que = PQueueCreate(cmp_func_ptr);
	p_que2 = PQueueCreate(cmp_func_ptr2);
	
	printf("%-33s:","ENQUE + DEQUE TEST");	
	
	/* initialise the lists */
	ListInit( p_que, 1);
	ListInit( p_que2, 2);
	
/*	printf("%d\n",*(int*)PQueueDq( p_que));*/
	
	memcmp( &element5, PQueueDq( p_que), sizeof(int)) == 0 && \
	memcmp( &string4, PQueueDq( p_que2), sizeof(string4)) == 0 ? \
	PASS : FAIL ;
	
	PQueueDestroy( p_que );
	PQueueDestroy( p_que2 );
}



void PeekTest()
{
	p_que_ty *p_que = NULL;
	p_que_ty *p_que2 = NULL;
	
	cmp_func_ty cmp_func_ptr = NumCompare;
	cmp_func_ty cmp_func_ptr2 = WordCompare;
	
	p_que = PQueueCreate(cmp_func_ptr);
	p_que2 = PQueueCreate(cmp_func_ptr2);
	
	ListInit( p_que, 1);
	ListInit( p_que2, 2);
	
	printf("%-33s:","PEEK TEST");	
	
	PQueueDq( p_que);
	PQueueDq( p_que);
	
	PQueueDq( p_que2);
	PQueueDq( p_que2);
		
	memcmp( &element2, PQueuePeek( p_que), sizeof(int)) == 0 &&		\
	memcmp( &string1, PQueuePeek( p_que2), sizeof(string1)) == 0 && \
	memcmp( &element2, PQueueDq( p_que), sizeof(int)) == 0 && 		\
	memcmp( &string1, PQueueDq( p_que2), sizeof(string1)) == 0 		\
	? PASS : FAIL;
	
	PQueueDestroy( p_que );
	PQueueDestroy( p_que2 );
}



void SizeTest()
{
	size_t size_before = 0;
	size_t size_after = 0;
	
	cmp_func_ty cmp_func_ptr = NumCompare;
	
	p_que_ty *p_que = NULL;
	
	p_que = PQueueCreate(cmp_func_ptr);
	
	/* initialise the lists */
	ListInit( p_que, 1);
	
	size_before = PQueueSize( p_que);
	
	PQueueDq( p_que);
	
	size_after = PQueueSize( p_que);
	
	PQueuePeek( p_que);
	
	printf("%-33s:","SIZE TEST");	
		
	size_before - size_after == 1 && size_after == PQueueSize( p_que) ? PASS :FAIL;
								
	PQueueDestroy( p_que );
}

void ClearTests()
{	
	cmp_func_ty cmp_func_ptr = NumCompare;
	
	p_que_ty *p_que = NULL;

	p_que = PQueueCreate(cmp_func_ptr);

	/* initialise the list */
	ListInit( p_que, 1);
	
	printf("%-33s:","CLEAR TEST");
	
	PQueueClear(p_que);
	
	PQueueSize( p_que) == 0 ? PASS : FAIL;
	
	PQueueDestroy( p_que );

}

void EraseTest()
{
	char param[] = "home";
	char *tester = NULL;
	
	match_func_ty match_param_ptr = MatchParam;
	
	cmp_func_ty cmp_func_ptr = WordCompare;
	
	p_que_ty *p_que = NULL;

	p_que = PQueueCreate(cmp_func_ptr);
	
	/* initialise the lists */
	ListInit( p_que, 2);
	
	printf("%-33s:","ERASE TEST");
	
	tester = PQueueErase(p_que, match_param_ptr, param);
	
	memcmp( tester, param, sizeof(param) )== 0 ? PASS : FAIL ;
	
	PQueueDestroy( p_que );
}



/*************************** 		helper funcs 		***********************/

void ListInit(p_que_ty *p_que, int var)
{
	if (1 == var)
	{
		PQueueNq( p_que, &element1);	
		PQueueNq( p_que, &element2);	
		PQueueNq( p_que, &element3);
		PQueueNq( p_que, &element4);
		PQueueNq( p_que, &element5);	
	}
	
	if (2 == var)
	{
		PQueueNq( p_que, &string1);	
		PQueueNq( p_que, &string2);	
		PQueueNq( p_que, &string3);
		PQueueNq( p_que, &string4);
		PQueueNq( p_que, &string5);	
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




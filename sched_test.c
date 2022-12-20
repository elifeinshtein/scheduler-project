/******************************************************************************
* Project : 	Scheduler test
* Author: 	Eli Feinshtein	
* Date: 	2022-11-03
* Version: 	1.0
*******************************************************************************/
#define _POSIX_C_SOURCE >= 2
#define _DEFAULT_SOURCE

#include <stdio.h>  /* printf */
#include <string.h> /* strcpy , strcmp*/
#include <stdlib.h> /* malloc ,free*/
#include <time.h>	

#include "sched.h"
#include "task.h"
#include "utils.h"
#include "test_utils.h"

#define ZEROTEST success_counter_g = 0;

#define ARR_SIZE 5			/* ammount of values in array */
#define VAL_LIMIT 6 		/* max value posiible for rand func */
#define UFAMMOUNT 8			/* ammount of user functions */


/*******************	 GLOBAL VARIABLES FOR TEST 			*******************/	

struct test
{
	int nums[ARR_SIZE];
	int times[ARR_SIZE];
	uid_ty uid[ARR_SIZE];
	
}*g_tester;

	
/****************************       FORWARD DECLARATIONS		***************/
/* test functions */
void TestStructCreate();
void TestStructDestroy();
void CreateDestroyTest();
void AddSizeTest();
void IsEmptySize();
void RemoveTest();
void RunTest();


/* user functions */
int AddParam(void *data);
int SquareParam(void *data);
int PrintVal(void *data);
int OpenWebSite(void *params);
int Beep(void *data);
int PopMessage(void *params);
int SchedStopWrap(void *params);
int FailParam(void *data);


/***********		 tester funcs  and variables			*******************
*
* For more functions - update the UFANNOUNT and UserFunc accordingly
*
* The SchedStopWrap and FailParam need to be Added manually for testing
*
* ammount is the ammount of random Adds to sched , 

* timelimit is the maximum time interval can be randomized
*
*******************************************************************************/

operation_func_ty UserFunc[UFAMMOUNT] = 
{ 
	AddParam, 
	SquareParam, 
	PrintVal, 
	OpenWebSite, 
	Beep,
	PopMessage,
	SchedStopWrap, 
	FailParam
};

/* creates an array of random numbers from 0 to limit */
static void RandomIntArray( int *rand_arr, size_t size_of_array, size_t limit);

/* creates (if needed) and initialises sched  */
static sched_ty *SchedInit( sched_ty *, size_t timelimit, size_t ammount);

/**************************         MAIN            ***************************/

int main() 
{
	/* malloc the test struct */
	TestStructCreate();
		
	CreateDestroyTest();
	AddSizeTest();
	IsEmptySize();
	RemoveTest();
	RunTest();
	
	PASSED;
	/* free the test dtruct */
	TestStructDestroy();
	(void)success_counter_g;
	(void)test_counter_g;				
	return 0;	
}


/*************************** 		TEST FUNCS			***********************/
void CreateDestroyTest()
{
	sched_ty *sched;
	
	sched = SchedCreate();
		
	SchedDestroy(sched);
	
	TEST("CREATE DESTROY TEST", 1, 1);

}


void AddSizeTest()
{
	size_t num_of_adds = 3;
	
	sched_ty *sched = NULL;
	sched = SchedInit( sched, 5, num_of_adds );	

	TEST("ADD + SIZE TEST", (int)SchedSize(sched), (int)(num_of_adds));
	
	SchedDestroy(sched);
}


void IsEmptySize()
{
	size_t i = 0;
	size_t num_of_adds = 2;
	
	sched_ty *sched = NULL;
	
	for(i = 0; i < num_of_adds ; ++i)
	{
		sched = SchedInit( sched, 5, i );		
		TEST( "ISEMPTY + SIZE TEST", SchedIsEmpty(sched), (int)(num_of_adds -i -1));	
	}	
	
	SchedDestroy(sched);
}

void RemoveTest()
{
	size_t i = 0;
	size_t num_of_adds = 3;
	
	sched_ty *sched = NULL;
	sched = SchedInit( sched, 5, num_of_adds );
	
	for(i = 0; i < num_of_adds ; ++i)
	{				
		SchedRemove(sched, g_tester->uid[i] );
		TEST( "REMOVE TEST", SchedSize(sched), (num_of_adds -1 -i) );
	}
	
	TEST( "REMOVE TEST", SchedSize(sched), 0);
	TEST( "REMOVE TEST", (int)SchedRemove(sched, g_tester->uid[i] ) , 1);
	
	SchedDestroy(sched);	
}

void RunTest()
{
	sched_ty *sched = NULL;
	int stop_time = 5;
	time_t now = time(NULL);
	size_t num_of_adds = 4;
	
	sched = SchedInit( sched, 5, num_of_adds );
		
	SchedAdd(sched, SchedStopWrap, sched, stop_time); 		/* adding Stop */
	
	SchedRun(sched);
	
	SchedAdd(sched, FailParam, 0, stop_time);				/* adding Fail */
	
	SchedRun(sched);
	
	TEST( "RUN TEST", time(NULL) - now, stop_time + stop_time);		

	SchedDestroy(sched);
}


/****************************		USER FUNCS	******************************/


int AddParam(void *data)
{
	*(int*)data += 15;	
	printf("AddParam result is %d\n",*(int*)data);
	
	return 1;
}


int SquareParam(void *data)
{
	*(int*)data *= *(int*)data;	
	printf("SquareParam result is %d\n",*(int*)data);
	return 0;
}

int FailParam(void *data)
{
	(void)data;
	
	return -1;
}

int Beep(void *data)
{
	(void)data;
	fprintf(stdout, "\aBeep!\n" );
	return 1;
}

int SchedStopWrap(void *params)
{
	SchedStop((sched_ty*)params);
	return 0;	
} 

int OpenWebSite(void *params) 
{
	UNUSED(params);

	system("open http://www.google.com");

	return 0;  
}

int PrintVal(void *data)
{
	static int counter =0;
	UNUSED(data);

	printf("Test Message number %d\n",counter);
	++counter;
	return 1;
}

int PopMessage(void *params) 
{
	FILE* fp;
	UNUSED(params);
	
	fp = popen("zenity --info","r");
	if (fp==NULL)
	{
		perror("Pipe returned a error");
	} 
	else 
	{
		pclose(fp);
	}

	return 0;  
}

/***************** 			HELPER FUNCS 			***************************/



void TestStructCreate()
{
	g_tester = malloc(sizeof(*g_tester));
}

void TestStructDestroy()
{
	free(g_tester);
}


static sched_ty *SchedInit( sched_ty *sched, size_t timelimit, size_t ammount )
{	
	size_t i = 0;	
	int f_num = 0;
	static int count = 0;
	srand(time(NULL) + count);
	
	RandomIntArray( g_tester -> times, ARR_SIZE, VAL_LIMIT); 
	
	RandomIntArray( g_tester -> nums, ARR_SIZE, timelimit); 	
	
	/* create the sched struct if it is NULL */
	if (NULL == sched )
	{
		sched = SchedCreate();
	}
	
	if (0 == ammount )
	{
		return sched;
		++count;
	}
	
	for(i = 0; i < ammount; ++i)
	{	
		/* randomize the function number from UserFunc */	
		f_num = rand() % (UFAMMOUNT-2); 

		g_tester-> uid[i] = SchedAdd(sched, UserFunc[f_num], &g_tester-> nums[i], g_tester->times[i]);
	}
	
	++count;
	return sched;
}
	
void RandomIntArray( int *rand_arr, size_t size_of_array, size_t limit)
{	
	size_t i = 0;
	static int counter = 0;
	srand(time(NULL) + counter);
	
	for(i = 0; i < size_of_array; ++i)
	{ 
		rand_arr[i]= (rand() % (limit-1) )+ 1; 
	}

	++counter;
}






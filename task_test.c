/******************************************************************************
* Project : 	TASK
* Author: 	Eli Feinshtein
* Date: 	2022-11-03
* Version: 	1.0
*******************************************************************************/

#include <stdio.h>  /* printf */
#include <string.h> /* strcpy , strcmp*/
#include <stdlib.h> /* malloc ,free*/
#include <unistd.h> /* sleep */

#include "task.h"
#include "uid.h"
#include "test_utils.h"

/*******************	 GLOBAL VARIABLES FOR TEST 			*******************/	


	
/****************************       FORWARD DECLARATIONS		***************/
/* test functions */

void CreateDestroyTest();
void GetTimeTest();
void SetTimeTest();
void ExecuteTest();
void MatchUidTest();
void MatchTimeTest();

/* user functions */
int AddParam(void *data);
int SquareParam(void *data);
int FailParam(void *data);


/**************************         MAIN            ***************************/

int main() 
{
	CreateDestroyTest();
	GetTimeTest();
	SetTimeTest();
	ExecuteTest();
	MatchUidTest();
	MatchTimeTest();
	(void)success_counter_g;
	(void)test_counter_g;			
	return 0;	
}




/*************************** 		helper funcs 		***********************/
void CreateDestroyTest()
{
	task_ty *task;
	int a = 5;
	
	task = TaskCreate( AddParam, (void*)&a, 3);
		
	free(task);
	
	printf("%-33s:","CREATE DESTROY TEST");
	1 ? PASS : FAIL ;
}

void GetTimeTest()
{
	task_ty *task;
	int a = 5;
	time_t now = time(NULL);
	
	task = TaskCreate( AddParam, (void*)&a, 3);
			
	printf("%-33s:","GET TIME TEST");
	
	TaskGetTime(task) - now -3 == 0 ? PASS : FAIL ;
	
	free(task);
}


void SetTimeTest()
{
	task_ty *task;
	int a = 5;
	time_t interval = 3;
	int delay = 2;
	time_t now = time(NULL);
	
	task = TaskCreate( AddParam, (void*)&a, interval);
			
	printf("%-33s:","SET TIME TEST");
	now = time(NULL);
	sleep(delay);
	
	TaskSetTime(task);

	TaskGetTime(task) - now == delay + interval ? PASS : FAIL ;
	
	free(task);
}

void ExecuteTest()
{
	task_ty *task[3];
	int i=0;
	int a = 5;
	int b = 3;
	
	task[0] = TaskCreate( AddParam, (void*)&a, 3);
	task[1] = TaskCreate( SquareParam, (void*)&b, 3);
	task[2] = TaskCreate( FailParam, (void*)&a, 3);
			
	printf("%-33s:","EXECUTE TEST");
	
	TaskExecute(task[0]) == 0 &&  a == 20 &&
	TaskExecute(task[1]) == 1 &&  b == 9  && 
	TaskExecute(task[2]) == -1  ? PASS : FAIL ;
	
	for(i = 0; i < 3; ++i)
	{
		free(task[i]);
	}
	
}


void MatchUidTest()
{
	task_ty *task[3];
	uid_ty uid;
	int i=0;
	int a = 5;
	int b = 3;
	int tester[3] = {0};
	
	task[0] = TaskCreate( AddParam, (void*)&a, 3);
	task[1] = TaskCreate( SquareParam, (void*)&b, 3);
	task[2] = TaskCreate( FailParam, (void*)&a, 3);
			
	printf("%-33s:","GET UID + MATCH UID TEST");
	
	uid = TaskGetUid(task[2]);
	
	for(i = 0; i < 3; ++i)
	{
		tester[i] = TaskMatchUid( task[i], uid );
	}
	
	tester[0] == 1 && tester[1] == 1 && tester[2] == 0  ? PASS : FAIL ;
	
	for(i = 0; i < 3; ++i)
	{
		free(task[i]);
	}
}

void MatchTimeTest()
{
	task_ty *task[3];
	int i=0;
	int a = 5;
	int b = 3;
	int tester[4] = {0};
	
	task[0] = TaskCreate( AddParam, (void*)&a, 3);
	task[1] = TaskCreate( SquareParam, (void*)&b, 5);
	task[2] = TaskCreate( FailParam, (void*)&a, 1);
			
	printf("%-33s:","MATCH TIME TEST");
	
	tester[0] = TaskMatchTime( task[0], task[1] );
	tester[1] = TaskMatchTime( task[1], task[2] );
	tester[2] = TaskMatchTime( task[0], task[2] );
	tester[3] = TaskMatchTime( task[1], task[1] );

	tester[0] < 0 && tester[1] > 0 && tester[2] > 0 && tester[3] == 0 ? PASS : FAIL ;
	
	for(i = 0; i < 3; ++i)
	{
		free(task[i]);
	}
}

/****************************		user funcs	******************************/



int AddParam(void *data)
{
	*(int*)data += 15;	
	
	return 0;
}


int SquareParam(void *data)
{
	*(int*)data *= *(int*)data;	
	
	return 1;
}

int FailParam(void *data)
{
	(void)data;
	
	return -1;
}





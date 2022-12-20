/*******************************************************************************
Project:	Scheduler project - Task 
Author: 	Eli Feinshtein
Date: 		7/11/2022
version 	1.0
*******************************************************************************/

#include <time.h>	/* time_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */


#include "uid.h"	/* uid_ty */
#include "task.h"	/* task_ty */
#include "utils.h"	/* MALLOC_TEST */

struct task	
{
  uid_ty uid;				
  int (*operation_func)(void* params); 
  void *params; 	  
  time_t interval;   
  time_t time_to_run;
};

enum return_val 
{
	SUCCESS = 0,	
	FAIL = 1	
}; 


task_ty *TaskCreate(int (*operation_func)(void* params), \
												void *params, time_t interval)
{
	/* create pointer to task struct */
	task_ty *task = NULL;
	
	/* create time variable with current time */
	time_t now = time(NULL);
	
	/* check if time succeeded */
	if( -1 == now )
	{
		return NULL;	
	}
	
	/* allocate memory for the slist */
	task = (task_ty *) malloc( sizeof(task_ty ) );
	
	/* test if malloc succeeded */
	MALLOC_TEST( task == NULL , NULL, "alloc fail",  NULL,  NULL)
	
	/* initialize the task struct */ 	
	task -> uid 		= UIDCreate();
	task -> operation_func = operation_func;
	task -> params 		= params;
	task -> interval 	= interval;
	task -> time_to_run = now + interval;
	
	return task;
}


void TaskDestroy(task_ty *task)
{
	/* assert the task pointer */
	assert(task && "task ptr isn't valid");
	
	/* free the task pointer */
	free(task);
	task = NULL;
}


uid_ty TaskGetUid(const task_ty *task)
{
	/* assert the task pointer */
	assert(task && "task ptr isn't valid");
	
	return task -> uid ;
}


int TaskSetTime(task_ty *task)
{
	/* create time variable with current time */
	time_t now = time(NULL);
	
	if( -1 == now )
	{
		return FAIL;	
	}
	
	/* assert the task pointer */
	assert(task && "task ptr isn't valid");
	
	/* update the time_to_run */
	task -> time_to_run = now + (task -> interval);
	
	return SUCCESS;
}


time_t TaskGetTime(const task_ty *task)
{
	/* assert the task pointer */
	assert(task && "task ptr isn't valid");
	
	return task -> time_to_run ;
}


int TaskExecute(task_ty *task)
{
	/* assert the task pointer */
	assert(task && "task ptr isn't valid");
	
	return task -> operation_func( task -> params);
}


int TaskMatchUid(const task_ty *task, uid_ty uid)
{
	/* assert the task pointer */
	assert(task && "task ptr isn't valid");
	
	/* return the result of uidissame function */
	return !UIDIsSameUID( uid,TaskGetUid(task) );
}


int TaskMatchTime(const task_ty *task1, const task_ty *task2)
{
	time_t diff;
	
	/* assert the tasks pointers */
	assert(task1 && "task1 ptr isn't valid");
	assert(task2 && "task2 ptr isn't valid");
	
	diff = (task1 -> time_to_run) - (task2 -> time_to_run) ;
	
	if( 0 == diff )
	{
		return 0;
	}
	
	return diff < 0 ? -1: 1;
}






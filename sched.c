/*******************************************************************************
Project:	Scheduler project
Author: 	Eli Feinshtein
Date: 		7.11.2022
*******************************************************************************/
#include <stdlib.h> 	/* malloc */
#include <assert.h> /* assert */
#include <unistd.h> /* sleep */
	
#include "sched.h"
#include "utils.h"		/* MALLOC_TEST */
#include "uid.h" 		/* uid_ty */
#include "task.h"		/* task_ty */
#include "p_queue.h"	/* p_queue_ty */

#define PQUEUE sched -> tasks_queue


/***************************		ENUMS			***************************/

struct scheduler
{
	p_que_ty *tasks_queue;
 	int to_stop;
 	task_ty *curr_task;
};

enum values
{
	TRUE = 1
};

enum return_vals
{
	UID_NOT_FOUND = 1,
	SUCCESS = 0,
	TASKFAIL = -1,
	STOPPED = 1
};

enum stops
{
	RUN = 0,
	STOP = 1
};

/************************* Forward Declerations *******************************/

static int MatchUidWrap(const void *task_to_match, const void *uid);


/***********************  			FUNCTIONS 		***************************/

sched_ty *SchedCreate(void)
{
	/* create pointer to task struct */
	sched_ty *sched = NULL;
	
	/* create and initialize pointer to p_queue */	
	p_que_ty *tasks_queue = NULL;
	
	/* allocate memory for the tasks_queue */
	tasks_queue = PQueueCreate( (cmp_func_ty)TaskMatchTime );
		
	/* test if malloc succeeded */
	MALLOC_TEST( NULL == tasks_queue , NULL, "alloc fail",  NULL,  NULL);	
	
	/* allocate memory for the slist */
	sched = (sched_ty *) malloc( sizeof(sched_ty ) );
	
	/* test if malloc succeeded , if not - free tasks_queue */
	MALLOC_TEST( NULL == sched , NULL, "alloc fail",  tasks_queue,  NULL);	
	
	/* initialize the scheduler struct */
	sched -> tasks_queue = tasks_queue;
	sched -> to_stop = ZERO;
	sched -> curr_task = NULL;
	
	return sched;
}


void SchedDestroy(sched_ty *sched)
{
	/* assert the task pointer */
	assert(sched && "sched ptr isn't valid");
	
	/* clear the sched queue and free all tasks */
	SchedClear(sched);
	
	/* destroy and free the p_queue struct */
	PQueueDestroy(PQUEUE);
	PQUEUE = NULL;
	
	/* free the sched struct */
	free(sched);
	sched = NULL;
	
}


uid_ty SchedAdd(sched_ty *sched, operation_func_ty oper_func,  void *params, 
				size_t interval)
{
	task_ty *new_task = NULL;

	/* assert */
	assert(sched && "sched ptr isn't valid");
	assert( ZERO < interval && "time interval isn't valid");
	assert(oper_func  && "oper_func ptr isn't valid");
	
	/* create a new task */
	new_task = TaskCreate( oper_func, params, interval);
	
	/* test if the creation succeeded, if not return baduid */
	VALCHECK( new_task, NULL, g_bad_uid)
	
	/* Enqueue the new task in the scheduler queue */
	PQueueNq( PQUEUE, new_task);
	
	/* retrun the new task uid*/
	return TaskGetUid(new_task);	
}


int SchedRemove(sched_ty *sched, uid_ty uid)
{
	task_ty *task_to_remove = NULL;
	
	/* assert the sched pointer */
	assert(sched && "sched ptr isn't valid");
	
	/* find the task that matches the uid given */
	task_to_remove = PQueueErase( PQUEUE, MatchUidWrap, &uid);
	
	/* test if task_to_remove equals to NULL, if it is return  UID_NOT_FOUND */
	VALCHECK(task_to_remove, NULL, UID_NOT_FOUND)
	
	/* destroy the task */
	TaskDestroy(task_to_remove);
	
	return SUCCESS;
}


int SchedRun(sched_ty *sched)
{
	int return_val = -2;
	time_t time_to_run = 0;
	unsigned int time_to_sleep = 0;
	time_t now = 0;
	
	/* assert the sched pointer */
	assert(sched && "sched ptr isn't valid");
	
	sched->to_stop = RUN;
	
	/* run while to_stop isnt 1 and the sched queue is not empty */
	while ( STOP != sched->to_stop && !SchedIsEmpty(sched) )
	{
		now = time(NULL);
		
		/* check if time failed */
		if(TASKFAIL == now)
		{
			return TASKFAIL;
		}
		
		/* dequeue the first task in the list */
		sched->curr_task = PQueueDq(PQUEUE);
		
		time_to_run = TaskGetTime(sched->curr_task);
		
		/* check if time of execution didnt pass */
		if( now <= time_to_run)
		{							
			time_to_sleep = sleep( time_to_run - now);
			
			/* wait paitently untill your time comes to shine */
			while ( ZERO != time_to_sleep)
			{
				time_to_sleep = sleep( time_to_sleep);
			}
		}			
		
		/* execute the task and fetch the return val of execution func */
		return_val = TaskExecute(sched->curr_task);
		
		/* if execution faile return TASKFAIL */
		if(TASKFAIL == return_val)
		{
			TaskDestroy(sched->curr_task);
			return TASKFAIL;		
		}
		
		/* if the task is repetitive */
		if(return_val)
		{
			/* update the time to run of current task*/
			TaskSetTime(sched->curr_task);
			
			/* insert the updated task back to the queue */
			PQueueNq( PQUEUE, sched->curr_task);
		}
		/* destroy task if not repetitive */
		else
		{
			TaskDestroy(sched->curr_task);
		}	
	}
	
	/* return 1 if stopped and 0 if succeeded */
	return sched->to_stop ? STOPPED : SUCCESS;
}


void SchedStop(sched_ty *sched)
{
	/* assert the sched pointer */
	assert(sched && "sched ptr isn't valid");
	
	/* update the value of to_stop in shced struct to 1 */
	sched -> to_stop = STOP;
}


int SchedIsEmpty(const sched_ty *sched)
{
	/* assert the task pointer */
	assert(sched && "sched ptr isn't valid");
	
	/* test if tasks_queue is empty and return 1 if it is , 0 if not */
	return PQueueIsEmpty(PQUEUE);
}


size_t SchedSize(const sched_ty *sched)
{
	/* assert the task pointer */
	assert(sched && "sched ptr isn't valid");

	return PQueueSize(PQUEUE);
}


void SchedClear(sched_ty *sched)
{
	/* assert the task pointer */
	assert(sched && "sched ptr isn't valid");
	
	/* run until the scheduler queue is empty */
	while( !SchedIsEmpty(sched))
	{
		/* destroy the current task and free the allocated memory */
		TaskDestroy( PQueueDq(PQUEUE));
	}
}


/************************		HELPER FUNCS		***************************/

static int MatchUidWrap(const void *task_to_match, const void *uid)
{
	return TaskMatchUid(task_to_match, *(uid_ty*)uid);
}














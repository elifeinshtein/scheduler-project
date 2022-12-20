/*******************************************************************************
Project:	Scheduler - Task - API
Author: 	Eli Feinshtein
Date: 		7/11/2022
version 	1.0
*******************************************************************************/
#ifndef __TASK_H__
#define __TASK_H__

#include <time.h>	/*time_t*/

#include "uid.h"	/*uid_ty*/

typedef struct task task_ty;


/*Description: 	Create task with the given arguments 
 *Arguments: 	task_func -  Pointer to callback task_func.
 * 			  	params - User parametrs for task function.
 * 			    interval - Time from time zero (now) when the task is to be executed.
 *Complexity:	O(1)
 *Return:		Pointer to new_task_ty or NULL on memory allocation fail
 *Undefined Behavior: */
task_ty *TaskCreate(int (*operation_func)(void* params), void *params, 
					time_t interval);

/*Description:		Destroy the task.
 *Arguments: 		task_to_Destroy -  Pointer to the task to remove.
 *Complexity:	  	O(1)
 *Returned value:	None
 *Undefined Behavior:	Invalid tast_ty pointer*/
void TaskDestroy(task_ty *task_to_destroy);

/*Description:	Returns uid of a given task
 *Arguments:	task - Task pointer 
 *Complexity:	O(1)
 *Return:		The task uid member
 *Undefined Behavior:	Invalid tast_ty pointer*/
uid_ty TaskGetUid(const task_ty *task);

/*Description:  Update a task time_to_run member.
 *Arguments: 	task_to_update - Pointer to the task to update.
 *Complexity:	O(1)
 *Return:		void
 *Undefined Behavior:	Invalid tast_ty pointer, invalid curr_time*/
int TaskSetTime(task_ty *task_to_update);

/*Description: 	Get the time_to_run member of a task_ty.
 *Arguments:	task - A task_ty *,
 *Complexity:	O(1)
 *Return value	The time_to_run member of the task 
 *Undefined Behavior:	Invalid tast_ty pointer*/
time_t TaskGetTime(const task_ty *task);

/*Description: 	Excute the function in the task_func member of task_to_execute,
				using the params stored in the task_to_execute.
 *Arguments: 	task_to_execute - Pointer to a task_ty.
 *Complexity:	O(1)
 *Return: 		0 if the task was successfuk -1 if the task failed, 
 				1 if the task is to be repeated.
 *Undefined Behavior:	Invalid tast_ty pointer*/
int TaskExecute(task_ty *task_to_execute);

/*Description: 	Compares between a Task uid member and a uid.
 *Arguments: 	task - Pointer to a task_ty.
 				uid_to_cmp - A uid to compare by.
 *Complexity:	O(1)
 *Return: 		0 if a match was found, else otherwise.
 *Undefined Behavior:	Invalid tast_ty pointer*/
int TaskMatchUid(const task_ty *task, uid_ty uid_to_cmp);

/*Description: 	Compares between two tasks time_to_run member.
 *Arguments: 	task1 - Pointer to a task_ty.
 				task2 - Pointer to task_ty.
 *Complexity:	O(1)
 *Return: 		0 if time is equal, return < 0 if task1 time_to_run is 
 				earlier then task2, return > 0 if task1 time_to_run is later 
 				then task2.
 *Undefined Behavior:	Invalid tast_ty pointers*/
int TaskMatchTime(const task_ty *task1, const task_ty *task2);

#endif /* __TASK_H__*/



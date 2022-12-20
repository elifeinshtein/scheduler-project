/*******************************************************************************
Project:	Scheduler 
Author: 	Eli Feinshtein
Date: 		7/11/2022
version 	1.0
*******************************************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include<stddef.h> 	/*size_t*/

#include"uid.h"

/************************************Types*************************************/
typedef struct scheduler sched_ty;

/*the call back function should return 0 on success (no need to repeat), 
-1 on fail (terminates the run) and 1 on repeat*/
typedef int (*operation_func_ty)(void *params);


/************************* Forward Declerations *******************************/

/*Description: 	Creates a new scheduler.
 *Arguments:	void.
 *Return:		A pointer to the new scheduler.	NULL on memory 
 				allocation failure.
 *Complexity: 	O(1).
 *Undefined behavior:	*/
sched_ty *SchedCreate(void);

/*Description: 	Free the scheduler.
 *Arguments:	sched_ty pointer, pointing to the scheduler to be freed.
 *Return:		void.
 *Complexity: 	O(n).
 *Undefined behavior: 	Invalid pointer*/
void SchedDestroy(sched_ty *sched);

/*Description: 	Add a task to the scheduler by its interval.
 *Arguments:	sched - A pointer to the scheduler.
    	   		oper_func - Function pointer to the o callback func.
                params - Paramters used by the callback function.
				interval - The required execution time of the task in seconds 
				since the start of the scheduler run.
 *Return: 		The task UID, bad_uid in case of memory allocation fail.
 *Complexity:	O(n). n is the number of prior tasks in scheduler.
 *Undefine behavior : 	Invalide sched_ty pointer, invalid function pointer, 
 						invalid time interval
 *note:			The argument oper_func may be SchedStop function, if so the 
 				params argument should be the same as sched*/
uid_ty SchedAdd(sched_ty *sched, operation_func_ty oper_func,  void *params, 
				size_t interval); 

/*Description: 	Removes a task from the scheduler.
 *Arguments:	sched - A pointer to the scheduler.
 				uid -  The uid of the tesk to be removed.
 *Return: 		0 - Success , 1 - uid not found.
 *Complexity: 	O(n) n is number of prior task or total task if task not found
 *Undefine behavior : 	Invalide sched_ty pointer.*/
int SchedRemove(sched_ty *sched, uid_ty uid);

/*Description: 	Run the scheduler tasks is sequence until all tasks were 
				executed successfully, a task returned -1 (failed), or the
				SchedStop function was called.
 *Arguments:	sched - A pointer to the scheduler.
 *Return: 		0 - Finished all tasks ,-1 - if a task failed ,  
 				1 - if stopped by SchedStop.
 *Complexity: 	O(n) n is the total number of tasks including 
 				thier repeated iterations
 *Undefine behavior: 	Invalide sched_ty pointer. invalid or corrupted 
 						callback_func in the schedule*/
int SchedRun(sched_ty *sched);

/*Description: 	Stops the current run the schedule this function should only be 
				used with SchedAdd and be insert to the schedule at the desired 
				stop interval, as the oper_func argument. 
 				The params argument of SchedAdd should be sched.
 *Arguments:	sched - A pointer to the scheduler.
 *Return: 		void (TODO Note might need to be int)
 *Complexity: 	O(1)
 *Undefine behavior : 	Invalide sched_ty pointer, SchedStop is not called as
 						part of SchedAdd*/
void SchedStop(sched_ty *sched);

/*Description: 	Checks if the scheduler is empty.
 *Arguments:	sched - A pointer to the scheduler.
 *Return: 		1 if empty 0 else.
 *Complexity: 	O(1)
 *Undefine behavior:	Invalide sched_ty pointer.*/
int SchedIsEmpty(const sched_ty *sched);

/*Description: 	Checks if the scheduler is empty.
 *Arguments:	sched - A pointer to the scheduler.
 *Return: 		The number of task in the scheduler
 *Complexity: 	O(n)
 *Undefine behavior: 	Invalide sched_ty pointer.*/
size_t SchedSize(const sched_ty *sched);

/*Description: 	Remove all tasks from the scheduler .
 *Arguments:	sched - A pointer to the scheduler.
 *Return: 		void
 *Complexity : 	O(n)
 *Undefine behavior : invalide sched_ty pointer.*/
void SchedClear(sched_ty *sched);

#endif  /*__SCHEDULER_H__*/


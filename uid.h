/******************************************************************************
* Project : UID
* Author : Eli Feinshtein
* Date : 6.11.22
* Version : 1.0	
*******************************************************************************/
#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h> /* pid_t */


typedef struct uid uid_ty;

extern const uid_ty g_bad_uid;

struct uid
{
  pid_t pid;
  time_t time;
  size_t counter; 	 
};

/******************************************************************************/

/* Description: Create a new UID.
   Arguments: 
   Return: 	New UID identifier object.
   Complexity:	O(1)
   Undefine behavior:  */
uid_ty UIDCreate(void);

/* Description:	Compare UIDs.
   Arguments: 	two UIDs to compare.
   Return: 	1 if matching UIDs, 0 otherwise.
   Complexity:	O(1)
   Undefine behavior:  */
int UIDIsSameUID(uid_ty uid1, uid_ty uid2);

#endif  	/*__UID_H__*/

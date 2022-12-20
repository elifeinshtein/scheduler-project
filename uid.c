/******************************************************************************
* Project : UID
* Author :Eli Feinshtein	
* Date : 6.11.22
* Version : 1.0
*******************************************************************************/

#include <unistd.h> 	/* pid_t */
#include <sys/types.h> /* pid_t */
#include <time.h> 	/* time_t */
#include <limits.h> /* INT_MAX, INT_MAX, ULONG_MAX */

#include "uid.h"

const uid_ty g_bad_uid = {INT_MAX, INT_MAX, ULONG_MAX};

enum return_val
{
	SUCCESS = 1,
	FAIL = 0
};

/******************************************************************************/


uid_ty UIDCreate(void)
{
	/* declare the new UID struct */
	uid_ty new_uid;	
	
	/* initialise the counter as 0 for first run */
    static size_t uid_counter = 0;
	
	/* initialise the UID struct */
	new_uid.time = time(NULL);
	
	if( -1 == new_uid.time )
	{
		return g_bad_uid;
	}
	
	new_uid.pid = getpid();
	new_uid.counter = ++uid_counter;
	
	/* return the created UID */
	return new_uid;
}


int UIDIsSameUID(uid_ty uid1, uid_ty uid2)
{
	/* check if all members of the struct are the same - if yes return 1 */
	if (uid1.pid == uid2.pid && uid1.time == uid2.time && uid1.counter ==  uid2.counter)
	{
		return SUCCESS;
	}
	
	return FAIL;
}



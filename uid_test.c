/******************************************************************************
* Project : UID
* Author : Eli Feinshtein
* Date : 6.11.22
* Version : 1.0	
*******************************************************************************/

#include <time.h> 	/* time_t */
#include <stdio.h>  /* printf */
#include <unistd.h> /*sleep*/

#include "uid.h"
#include "test_utils.h"

extern const uid_ty g_bad_uid;


/******************************************************************************/



void UidTest();

int main() 
{
	(void)success_counter_g;
	(void)test_counter_g;
	UidTest();
				
	return 0;
	
}

void UidTest()
{
	uid_ty new_uid = g_bad_uid;	
	uid_ty new_uid2 = g_bad_uid;		
	uid_ty new_uid3 = g_bad_uid;		
	
	new_uid = UIDCreate();
	new_uid2 = UIDCreate();
	
	
	printf("uid 1 pid is is %d\n",new_uid.pid);
	printf("uid 1 timestamp is %ld\n",new_uid.time);
	printf("uid 1 counter is %ld\n",new_uid.counter);
	
	sleep(10);
	
	new_uid3 = UIDCreate();
	
	printf("uid 3 pid is is %d\n",new_uid3.pid);
	printf("uid 3 timestamp is %ld\n",new_uid3.time);
	printf("uid 3 counter is %ld\n",new_uid3.counter);
	
	printf("%-33s:","ISSAME UID TEST");	
	
	0 == UIDIsSameUID(new_uid,new_uid2) && \
	UIDIsSameUID(new_uid,new_uid) && \
	0 == UIDIsSameUID(new_uid3, new_uid2)? PASS : FAIL ;
}

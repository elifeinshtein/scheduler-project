/******************************************************************************
* Project: 	UTILS
* Author: 	Eli Feinshtein	
* Date: 	2022-10-27
* Version:	1.0 

*******************************************************************************/
#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h> /*fputs*/

/*DEBUG_ONLY code*/ 
#ifndef NDEBUG /* debug mode */
#define DEBUG_ONLY(x) x
#else /* release mode */
#define DEBUG_ONLY(x) 
#endif

#define P(var) printf(""#var" %ld\n",var);
#define PA(var) printf(""#var" %p\n",(void*)var);

#define UNUSED(x) (void)(x)

#define ZERO 0

#define WORD sizeof(size_t)

#define ABS(a) ( (a) < 0 ? -(a) : (a))
#define MAX(a,b) ( (a)<(b)  ? (b) : (a) )

#define MALLOC_TEST(is_good, ret, msg, free1, free2)\
if( is_good )										  \
{ 						\
	fputs(msg,stderr);  \
	return ret; 		\
	free(free1); 		\
	free(free2); 		\
}; 

#define VALCHECK( tested_val ,test, ret)\
if( tested_val == test )							 \
{ 						\
	return ret; 		\
}; 


 
#endif /*__UTIL_H_*/

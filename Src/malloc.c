/*
 * malloc.c
 *
 *  Created on: 5 juin 2019
 *      Author: laetitia
 */


#include <stdlib.h>
#include "FreeRTOS.h"
#include <task.h> // pvxxxMalloc
#include <portable.h> // pvxxxMalloc
#include <string.h> // memset

/* From :
https://www.freertos.org/FreeRTOS_Support_Forum_Archive/October_2009/freertos_malloc_function_in_FreeRTOS_3444349.html */

/* Defining malloc/free should overwrite the standard versions provided by the compiler. */

void *malloc (size_t size)
{
	/* Call the FreeRTOS version of malloc. */
	return pvPortMalloc( size );
}

void *calloc (size_t nmemb, size_t size)
{
	/* Call the FreeRTOS version of calloc. */

	void * p= pvPortMalloc( size );
	return memset(p,0,size);
}

void free (void *ptr) { /* Call the FreeRTOS version of free.*/

	vPortFree( ptr );

}


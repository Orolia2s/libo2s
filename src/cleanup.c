#include "o2s/cleanup.h"

#include <stdlib.h> // free

/**
 * Given the address of a pointer, this pointer is passed to free if its value is not NULL
 */
void cleanup_allocated_memory(void** address)
{
	if (*address)
		free(*address);
}

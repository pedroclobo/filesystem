/*
 * File: utils.c
 * Author: Pedro Lobo
 * Description: Utility functions.
 */

#include "proj2.h"

void *
safe_malloc(size_t size) {
	void *p = malloc(size);

	if (p != NULL)
		return p;

	printf(ERROR_NO_MEMORY);
	exit(1);

	return NULL;
}

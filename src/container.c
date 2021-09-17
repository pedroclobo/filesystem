/*
 * File: container.c
 * Author: Pedro Lobo
 * Description: Functions for the global storage structure.
*/

#include "proj2.h"

/*
 * Initialize container structure.
 * Assign often used directory functions,
 * initialize the directories hash table,
 * add the root directory, parent of all directories.
 */
void
init_container(container * global) {
	global->key_name = get_directory_name;
	global->key_value = get_directory_value;
	global->less = directory_less;
	global->print = print_directory;
	global->name = init_hashtable(HASH_INITIAL_SIZE);
	global->value = init_hashtable(HASH_INITIAL_SIZE);
}

/*
 * Free container structure from the heap,
 * along with and all its fields.
 */
void
free_container(container * global) {
	free_hashtable(global->name, 1);
	free_hashtable(global->value, 0);
}

#include "proj2.h"

/* Hashing function */
int hash_string(char* string, int size)
{
	long int hash, a = 31415, b = 27183;

	for (hash = 0; *string != '\0'; string++, a = a * b % (size - 1)) {
		hash = (a * hash + *string) % size;
	}

	return hash;
}

/* Initialize hash table */
void hash_init(hashtable *hash_t, int size)
{
	int i;

	hash_t->table = (void**) malloc(size * sizeof(void*));
	hash_t->size = size;
	hash_t->count = 0;

	for (i = 0; i < size; i++) {
		hash_t->table[i] = NULL;
	}
}

/* Insert item in the hash table */
void hash_insert(hashtable *hash_t, void *item, char* (*key)(void*))
{
	int i = hash_string(key(item), hash_t->size);

	/* Linear Probing */
	while (hash_t->table[i] != NULL) i = (i + 1) % hash_t->size;

	hash_t->table[i] = item;
	hash_t->count++;
}

/* Search the hash table for an item given its key */
void *hash_search(hashtable *hash_t, char *value, char* (*key)(void*))
{
	int i = hash_string(value, hash_t->size);

	while (hash_t->table[i] != NULL)
		if (!strcmp(key(hash_t->table[i]), value))
			return hash_t->table[i];
		else
			i = (i + 1) % hash_t->size;

	return NULL;
}

/* Delete an item from the hash table given its key,
 * not freeing the item from memory */
void hash_delete(hashtable *hash_t, char *value, char* (*key)(void*))
{
	int i = hash_string(value, hash_t->size);

	while (hash_t->table[i] != NULL)
		if (!strcmp(key(hash_t->table[i]), value)) {
			hash_t->table[i] = NULL;
			hash_t->count--;
		}
		else
			i = (i + 1) % hash_t->size;
}

void hash_print(hashtable *hash_t, void (*print)(void*))
{
	int i;

	for (i = 0; i < hash_t->size; i++)
		if (hash_t->table[i] != NULL)
			print(hash_t->table[i]);
}

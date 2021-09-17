/*
 * File: hash.c
 * Author: Pedro Lobo
 * Description: Hash table data structure functions.
 */

#include "proj2.h"

/* Hashing function */
int
string_hash(char *string, int size) {
	long hash, a = 31415, b = 27183;

	for (hash = 0; *string != '\0'; string++, a = a * b % (size - 1)) {
		hash = (a * hash + *string) % size;
	}

	return hash;
}

/* Initialize hash table */
hashtable *
init_hashtable(int size) {
	int i;
	hashtable *hash_t = (hashtable *) safe_malloc(sizeof(hashtable));

	hash_t->table = (void **) safe_malloc(size * sizeof(void *));
	hash_t->size = size;
	hash_t->count = 0;

	for (i = 0; i < size; i++) {
		hash_t->table[i] = NULL;
	}

	return hash_t;
}

/*
 *
 */
hashtable *
expand_hashtable(hashtable * hash_t, char *(*key)(void *)) {
	int i = 0;
	hashtable *new = init_hashtable(hash_t->size * 2);

	for (i = 0; i < hash_t->size; i++) {
		if (hash_t->table[i] != NULL)
			insert_hashtable(&new, hash_t->table[i], key);
	}

	free_hashtable(hash_t, 0);

	return new;
}

/* Insert item in the hash table */
void
insert_hashtable(hashtable ** hash_t, void *item, char *(*key)(void *)) {
	int i;

	if (key(item) == NULL)
		return;

	i = string_hash(key(item), (*hash_t)->size);

	/* Linear Probing */
	while ((*hash_t)->table[i] != NULL)
		i = (i + 1) % (*hash_t)->size;
	(*hash_t)->table[i] = item;
	(*hash_t)->count++;

	if ((*hash_t)->count > ((*hash_t)->size / 2))
		*hash_t = expand_hashtable(*hash_t, key);
}

/* Search the hash table for an item given its key */
void *
search_hashtable(hashtable * hash_t, char *item_key, char *(*key)(void *)) {
	int i = string_hash(item_key, hash_t->size);

	while (hash_t->table[i] != NULL)
		if (!strcmp(key(hash_t->table[i]), item_key))
			return hash_t->table[i];
		else
			i = (i + 1) % hash_t->size;

	return NULL;
}

/*
 * Delete an item from the hash table given its key,
 * not freeing the item from memory.
 */
void
delete_hashtable(hashtable * hash_t, char *item_key, char *(*key)(void *)) {
	int i;

	if (item_key == NULL)
		return;

	i = string_hash(item_key, hash_t->size);

	while (hash_t->table[i] != NULL)
		if (!strcmp(key(hash_t->table[i]), item_key)) {
			hash_t->table[i] = NULL;
			hash_t->count--;
		} else
			i = (i + 1) % hash_t->size;
}

/* Destory hash table */
void
free_hashtable(hashtable * hash_t, int delete_all) {
	directory *dir = NULL;
	int i;

	/* Free all directories */
	if (delete_all == 1) {
		for (i = 0; i < hash_t->size; i++) {
			if (hash_t->table[i] != NULL) {
				dir = (directory *) hash_t->table[i];
				free_directory(dir);
			}
		}
	}
	free(hash_t->table);
	free(hash_t);
}

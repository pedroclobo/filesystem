#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Data Structures
 */

/* Linked List */
typedef struct list_node {
	void *data;
	struct list_node *next;
} list_node;

/* Tree */
typedef struct tree_node {
	void *data;
	struct tree_node *left;
	struct tree_node *right;
} tree_node;


/*
 * Structures
 */

/* Dicretory */
typedef struct {
	char *path;
	list_node *subpaths_c;
	tree_node *subpaths_a;
} dir;


/*
 * Functions
 */

/* linked_list.c */
void list_insert(list_node **head, void *item);
void list_delete(list_node **head, void *item);
void list_traverse(list_node *head, void (*print)(void*));

/* directory.c */
dir *dir_new(char *path);
int dir_less(void *a, void *b);
void dir_print(void *a);

/* tree.c */
tree_node *tree_new(void *item);
void tree_insert(tree_node **root, void *item, int (*less)(void*, void*));
void tree_traverse(tree_node *root, void (*print)(void*));

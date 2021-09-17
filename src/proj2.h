/*
 * File: proj1.h
 * Author: Pedro Lobo
 * Description: Header file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Command Descriptions and Strings */
#define DESC_HELP "Imprime os comandos disponíveis."
#define DESC_QUIT "Termina o programa."
#define DESC_SET "Adiciona ou modifica o valor a armazenar."
#define DESC_PRINT "Imprime todos os caminhos e valores."
#define DESC_FIND "Imprime o valor armazenado."
#define DESC_LIST "Lista todos os componentes imediatos de um sub-caminho."
#define DESC_SEARCH "Procura o caminho dado um valor."
#define DESC_DELETE "Apaga um caminho e todos os subcaminhos."

/* Command Errors */
#define ERROR_FIND_NOT_FOUND "not found"
#define ERROR_FIND_NO_DATA "no data"
#define ERROR_LIST_NOT_FOUND "not found"
#define ERROR_SEARCH_NOT_FOUND "not found"
#define ERROR_NO_MEMORY "no memory"

/* Maximum command string size */
#define MAX_CMD_SIZE 65536

/* Hash Table */
#define HASH_INITIAL_SIZE 29

/* Strings */
#define WHITESPACE " \n\t"


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
	int height;
} tree_node;

/* Hash Table */
typedef struct {
	void **table;
	int count;
	int size;
} hashtable;


/*
 * Structures
 */

/* Path */
typedef struct {
	char *name;
	char *value;
} path;

/* Dicretory */
typedef struct {
	path *path;
	list_node *subpaths_c;
	tree_node *subpaths_a;
} directory;

/* Container */
typedef struct {
	hashtable *name;
	hashtable *value;

	/* Function Pointers */
	char *(*key_name)(void *);
	char *(*key_value)(void *);
	int (*less)(void *, void *, char *(void *));
	void (*print)(void *);

} container;

/*
 * Functions
 */

/* avl.c */
tree_node *tree_new(void *item);
int tree_height(tree_node * root);
void tree_update_height(tree_node * root);
tree_node *tree_rotL(tree_node * root);
tree_node *tree_rotR(tree_node * root);
tree_node *tree_rotLR(tree_node * root);
tree_node *tree_rotRL(tree_node * root);
int tree_balance_factor(tree_node * root);
tree_node *tree_balance(tree_node * root);
void tree_insert(tree_node ** root, void *item, char *(*key)(void *),
		 int (*less)(void *, void *, char *(void *)));
void tree_delete(tree_node ** root, void *item, char *(*key)(void *),
		 int (*less)(void *, void *, char *(void *)));
void tree_traverse(tree_node * root, void (*print)(void *));
void tree_free(tree_node * root);

/* linked_list.c */
void list_insert(list_node ** head, void *item);
void list_delete(list_node ** head, void *item);
void list_traverse(list_node * head, void (*print)(void *));
void list_free(list_node * head);
int list_contains(list_node * head, void *item);

/* hash.c */
int string_hash(char *string, int size);
hashtable *init_hashtable(int size);
void insert_hashtable(hashtable ** hash_t, void *item, char *(*key)(void *));
void *search_hashtable(hashtable * hash_t, char *item_key,
		       char *(*key)(void *));
void delete_hashtable(hashtable * hash_t, char *item_key, char *(*key)(void *));
void free_hashtable(hashtable * hash_t, int delete_all);

/* directory.c */
directory *new_directory(char *name, char *value);
void free_directory(directory * d);
char *get_directory_name(void *a);
char *get_directory_value(void *a);
void add_directory_value(directory * d, char *value);
directory *get_directory_by_name(char *name, container * global);
directory *get_directory_by_value(char *name, container * global);
int directory_exists(char *name, container * global);
void add_directory(char *name, char *value, container * global);
int has_subdirectories(directory * dir);
int is_subdirectory(directory * subdir, directory * dir);
void delete_subdirectory(directory * subdir, directory * dir,
			 container * global);
void add_subdirectory(directory * subdir, directory * dir, container * global);
void add_directory_recursively(char *name, char *value, directory * subdir,
			       container * global);
void remove_directory_recursively(directory * dir, container * global);
void delete_directory(char *name, container * global);
int directory_less(void *a, void *b, char *(*key)(void *));
void print_directory(void *a);
void print_subdirectories(directory * dir, container * global);
void remove_all_directories(container * global);

int list_lenght(list_node * head);

/* container.c */
void init_container(container * global);
void free_container(container * global);

/* path.c */
path *new_path(char *name, char *value);
void free_path(path * p);
int has_value(path * p);
char *get_path_name(path * p);
char *get_path_value(path * p);
void add_path_value(path * p, char *value);
int get_path_name_depth(char *name);
void get_parent_path_name(char *name, char **parent);
void get_child_path_name(char *name, char **child);
void trim_directory_name(char *name, char **res);

/* utils.c */
void *safe_malloc(size_t size);

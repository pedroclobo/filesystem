#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Command Descriptions */
#define DESC_HELP "Imprime os comandos disponíveis."
#define DESC_QUIT "Termina o programa."
#define DESC_SET "Adiciona ou modifica o valor a armazenar."
#define DESC_PRINT "Imprime todos os caminhos e valores."
#define DESC_FIND "Imprime o valor armazenado."
#define DESC_LIST "Lista todos os componentes imediatos de um sub-caminho."
#define DESC_SEARCH "Procura o caminho dado um valor."
#define DESC_DELETE "Apaga um caminho e todos os subcaminhos."

/* Memory Allocation Specifications */
#define MALLOC_SIZE 30
#define MALLOC_INC 20


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

/* Dicretory */
typedef struct {
	char *path;
	char *value;
	list_node *subpaths_c;
	tree_node *subpaths_a;
} dir;


/*
 * Functions
 */

/* avl.c */
tree_node *tree_new(void *item);
int tree_height(tree_node *root);
void tree_update_height(tree_node *root);
tree_node *tree_rotL(tree_node *root);
tree_node *tree_rotR(tree_node *root);
tree_node *tree_rotLR(tree_node *root);
tree_node *tree_rotRL(tree_node *root);
int tree_balance_factor(tree_node *root);
tree_node *tree_balance(tree_node *root);
void tree_insert(tree_node **root, void *item, int (*less)(void*, void*));
void tree_delete(tree_node **root, void *item, int (*less)(void*, void*));
void tree_traverse(tree_node *root, void (*print)(void*));

/* linked_list.c */
void list_insert(list_node **head, void *item);
void list_delete(list_node **head, void *item);
void list_traverse(list_node *head, void (*print)(void*));

/* hash.c */
int hash_string(char* string, int size);
void hash_init(hashtable *hash_t, int size);
void hash_insert(hashtable *hash_t, void *item, char* (*key)(void*));
void hash_print(hashtable *hash_t, void (*print)(void*));
void hash_delete(hashtable *hash_t, char *value, char* (*key)(void*));

/* directory.c */
dir *dir_new(char *path);
void dir_add_value(dir *d, char *value);
char *dir_key(void *a);
int dir_less(void *a, void *b);
void dir_print(void *a);

/* stdin.c */
void get_cmd(char **cmd);
char *get_cmd_flag(char *cmd);

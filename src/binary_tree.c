#include "proj2.h"

/* Create a new tree node */
tree_node *tree_new(void *item)
{
	tree_node *new = (tree_node*) malloc(sizeof(tree_node));
	new->data = item;
	new->left = new->right = NULL;

	return new;
}

/* Insert a new element in the tree */
void tree_insert(tree_node **root, void *item, int (*less)(void*, void*))
{
	if (*root == NULL)
		*root = tree_new(item);
	else if (less(item, (*root)->data))
		tree_insert(&(*root)->left, item, less);
	else
		tree_insert(&(*root)->right, item, less);
}

/* Print all the tree items */
void tree_traverse(tree_node *root, void (*print)(void*))
{
	if (root == NULL)
		return;

	tree_traverse(root->left, print);
	print(root->data);
	tree_traverse(root->right, print);
}

#include "proj2.h"

/* Create a new tree node */
tree_node *tree_new(void *item)
{
	tree_node *new = (tree_node*) malloc(sizeof(tree_node));
	new->data = item;
	new->height = 1;

	return new;
}

/* Return the max value tree node */
tree_node *tree_max(tree_node *root)
{
	if (root->right != NULL)
		tree_max(root->right);

	return root;
}

/* Return the height of the tree */
int tree_height(tree_node *root)
{
	if (root == NULL)
		return 0;

	return root->height;
}

/* Update the height of the tree, after operation */
void tree_update_height(tree_node *root)
{
	int h_left = tree_height(root->left);
	int h_right = tree_height(root->right);

	root->height = h_left > h_right ? h_left + 1 : h_right + 1;
}

/* Rotate left AVL operation */
tree_node *tree_rotL(tree_node *root)
{
	tree_node *tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;

	tree_update_height(root);
	tree_update_height(tmp);

	return tmp;
}

/* Rotate right AVL operation */
tree_node *tree_rotR(tree_node *root)
{
	tree_node *tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;

	tree_update_height(root);
	tree_update_height(tmp);

	return tmp;
}


/* Rotate left, then right AVL operation */
tree_node *tree_rotLR(tree_node *root)
{
	if (root == NULL)
		return root;

	root->left = tree_rotL(root->left);

	return tree_rotR(root);
}

/* Rotate right, then left AVL operation */
tree_node *tree_rotRL(tree_node *root)
{
	if (root == NULL)
		return root;

	root->right = tree_rotR(root->right);

	return tree_rotL(root);
}

/* Return the tree balance factor */
int tree_balance_factor(tree_node *root)
{
	if (root == NULL)
		return 0;

	return tree_height(root->left) - tree_height(root->right);
}

/* Balance the AVL tree */
tree_node *tree_balance(tree_node *root) {
	int balance_factor;

	if (root == NULL)
		return root;

	balance_factor = tree_balance_factor(root);

	if (balance_factor > 1) {
		if (tree_balance_factor(root->left) >= 0)
			root = tree_rotR(root);
		else
			root = tree_rotLR(root);
	}

	else if (balance_factor < -1) {
		if (tree_balance_factor(root->right) <= 0)
			root = tree_rotL(root);
		else
			root = tree_rotRL(root);
	}

	else
		tree_update_height(root);

	return root;
}

/* Insert item in the AVL tree */
void tree_insert(tree_node **root, void *item, int (*less)(void*, void*))
{
	if (*root == NULL)
		*root = tree_new(item);

	else if (less(item, (*root)->data))
		tree_insert(&(*root)->left, item, less);

	else
		tree_insert(&(*root)->right, item, less);

	*root = tree_balance(*root);
}

/* Delete item in the AVL tree */
void tree_delete(tree_node **root, void *item, int (*less)(void*, void*))
{
	tree_node *tmp = NULL;
	void *tmp_data = NULL;

	if (*root == NULL)
		return;

	else if (less(item, (*root)->data))
		tree_delete(&(*root)->left, item, less);

	else if (less((*root)->data, item))
		tree_delete(&(*root)->right, item, less);

	else {
		if ((*root)->left != NULL && (*root)->right != NULL) {
			tmp = tree_max((*root)->left);
			tmp_data = (*root)->data;
			(*root)->data = tmp->data;
			tmp->data = tmp_data;
			tree_delete(&(*root)->left, tmp->data, less);

		} else {
			tmp = (*root);
			if ((*root)->left == NULL && (*root)->right == NULL)
				(*root) = NULL;
			else if ((*root)->left == NULL)
				(*root) = (*root)->right;
			else
				(*root) = (*root)->left;
			free(tmp);
		}
	}
	(*root) = tree_balance((*root));
}

/* Traverse the AVL tree */
void tree_traverse(tree_node *root, void (*print)(void*))
{
	if (root == NULL)
		return;

	tree_traverse(root->left, print);
	print(root->data);
	tree_traverse(root->right, print);
}

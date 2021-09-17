#include "proj2.h"

/* Insert item at the end of the linked list */
void list_insert(list_node **head, void *item)
{
	list_node *tmp;

	list_node *new = (list_node*) safe_malloc(sizeof(list_node));
	new->data = item;
	new->next = NULL;

	if (*head == NULL) {
		*head = new;
		return;
	}

	for (tmp = *head; tmp->next != NULL; tmp = tmp->next)
		;

	tmp->next = new;
}

/* Delete item from the linked list */
void list_delete(list_node **head, void *item){
	list_node *prev = NULL, *curr = *head;

	while (curr != NULL && curr->data != item) {
		prev = curr;
		curr = curr->next;
	}

	if (curr != NULL) {
		if (prev != NULL)
			prev->next = curr->next;
		else
			*head = curr->next;

		free(curr);
	}
}

/* Traverse the list, printing the item keys */
void list_traverse(list_node *head, void (*print)(void*))
{
	list_node *tmp = head;

	while (tmp != NULL) {
		print(tmp->data);
		tmp = tmp->next;
	}
}

int list_contains(list_node *head, void *item)
{
	while (head != NULL) {
		if (head->data == item)
			return 1;
		head = head->next;
	}

	return 0;
}

/* Free all linked list nodes from memory */
void list_free(list_node *head) {
	list_node *curr = head;
	list_node *tmp = head;

	while (curr != NULL) {
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}

	head = NULL;
}

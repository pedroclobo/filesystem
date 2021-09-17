/*
 * File: directory.c
 * Author: Pedro Lobo
 * Description: Directory structure related functions.
 */

#include "proj2.h"

/*
 * Create a new directory structure,
 * including a path/value structure,
 * an AVL tree with all subdirectories and
 * a linked list with all subdirectories.
 */
directory *
new_directory(char *name, char *value) {
	directory *new = (directory *) safe_malloc(sizeof(directory));

	new->path = new_path(name, value);
	new->subpaths_a = NULL;
	new->subpaths_c = NULL;

	return new;
}

/*
 * Free directory structure from memory,
 * including the path/value structure,
 * the AVL tree and the linked list with all subdirectories.
 */
void
free_directory(directory * d) {
	if (d) {
		free_path(d->path);
		tree_free(d->subpaths_a);
		list_free(d->subpaths_c);
		free(d);
	}
}

/*
 * Get the directory name.
 */
char *
get_directory_name(void *a) {
	directory *b = (directory *) a;
	return get_path_name(b->path);
}

/*
 * Get the directory value.
 */
char *
get_directory_value(void *a) {
	directory *b = (directory *) a;
	return get_path_value(b->path);
}

/*
 * Add a value to the directory path
 * or change it if it already exists.
 */
void
add_directory_value(directory * d, char *value) {
	add_path_value(d->path, value);
}

/*
 * Search the directory storage structure for the directory
 * that contains a path with the given name.
 * Return a pointer to that directory.
 */
directory *
get_directory_by_name(char *name, container * global) {
	directory *d = search_hashtable(global->name, name, global->key_name);
	return d;
}

/*
 * Search the directory storage structure for the directory,
 * that contains a path with the given value.
 * Return a pointer to that directory.
 */
directory *
get_directory_by_value(char *value, container * global) {
	directory *d =
		search_hashtable(global->value, value, global->key_value);
	return d;
}

/*
 * Check if a directory path with the given name exists
 * in the directory storage structure.
 */
int
directory_exists(char *name, container * global) {
	directory *d = get_directory_by_name(name, global);

	/* Directory wasn't found */
	if (d == NULL)
		return 0;

	return 1;
}

/*
 * Add a directory to the system.
 * If it already exists, change its path value.
 */
void
add_directory(char *name, char *value, container * global) {
	directory *new = NULL;

	if (directory_exists(name, global))
		  add_directory_value(get_directory_by_name(name, global),
				      value);

	else {
		new = new_directory(name, value);
		insert_hashtable(&global->name, new, global->key_name);
		insert_hashtable(&global->value, new, global->key_value);
	}
}

/*
 * Delete a directory from the directory storage structure,
 * and free it from memory.
 */
void
delete_directory(char *name, container * global) {
	directory *d = NULL;

	if (!directory_exists(name, global))
		  return;

	d = get_directory_by_name(name, global);
	delete_hashtable(global->name, name, global->key_name);
	delete_hashtable(global->value, get_directory_value(d),
			 global->key_value);
	free_directory(d);
}

/*
 * Determines if a directory has any subdirectories.
 */
int
has_subdirectories(directory * dir) {
	return dir->subpaths_a != NULL;
}

/*
 * Determines if subdir is a subdirectory of dir.
 */
int
is_subdirectory(directory * subdir, directory * dir) {
	return list_contains(dir->subpaths_c, subdir);
}

/*
 * Add a directory as another directory's subdirectory.
 */
void
add_subdirectory(directory * subdir, directory * dir, container * global) {
	if (!is_subdirectory(subdir, dir)) {
		list_insert(&dir->subpaths_c, subdir);
		tree_insert(&dir->subpaths_a, subdir, global->key_name,
			    global->less);
	}
}

/*
 * Remove a directory as another directory's subdirectory.
 */
void
delete_subdirectory(directory * subdir, directory * dir, container * global) {
	if (is_subdirectory(subdir, dir)) {
		list_delete(&dir->subpaths_c, subdir);
		tree_delete(&dir->subpaths_a, subdir, global->key_name,
			    global->less);
	}
}

/*
 * Add a directory recursively.
 */
void
add_directory_recursively(char *name, char *value, directory * subdir,
			  container * global) {
	directory *dir = NULL;
	char *parent = (char *) safe_malloc((strlen(name) + 1) * sizeof(char));

	/* If directory doesn't exist, add it. Then get its reference. */
	if (!directory_exists(name, global))
		  add_directory(name, value, global);
	dir = get_directory_by_name(name, global);

	/* Add pending subdirectory */
	if (subdir != NULL)
		add_subdirectory(subdir, dir, global);

	/* Call function on parent directory */
	get_parent_path_name(name, &parent);
	if (strcmp(parent, "/"))
		add_directory_recursively(parent, NULL, dir, global);

	free(parent);
}

/*
 * Delete a directory recursively.
 */
void
remove_directory_recursively(directory * dir, container * global) {
	list_node *head = NULL;
	directory *updir = NULL;
	directory *subdir = NULL;

	/* Get parent info */
	char *name = get_directory_name(dir);
	char *parent = (char *) malloc((strlen(name) + 1) * sizeof(char));
	get_parent_path_name(name, &parent);
	updir = get_directory_by_name(parent, global);

	/* Call function on every subdirectory */
	if (has_subdirectories(dir)) {
		for (head = dir->subpaths_c; head->next != NULL;
		     head = head->next) {
			subdir = (directory *) (head->data);
			remove_directory_recursively(subdir, global);
		}
	}

	/* Delete directory from parent */
	delete_subdirectory(dir, updir, global);

	/* Delete the directory itself */
	delete_directory(get_directory_name(dir), global);

	free(parent);
}

void
remove_all_directories(container * global) {
	directory *root = get_directory_by_name("root", global);
	directory *dir = NULL;
	directory **dirs = NULL;
	list_node *head = NULL;
	int len = 0, i;

	for (head = root->subpaths_c; head != NULL; head = head->next) {
		len++;
	}

	dirs = (directory **) malloc(len * sizeof(directory *));

	for (i = 0, head = root->subpaths_c; head != NULL; head = head->next) {
		dirs[i++] = (directory *) head->data;
	}

	for (i = 0; i < len; i++) {
		dir = dirs[i];
		remove_directory_recursively(dir, global);
	}

	free(dirs);
}

/*
 * Directory comparison function.
 */
int
directory_less(void *a, void *b, char *(*key)(void *)) {
	return (strcmp(key(a), key(b)) < 0);
}

/* Directory print function */
void
print_directory(void *a) {
	directory *c = (directory *) a;

	char *child =
		(char *) safe_malloc((strlen(get_path_name(c->path) + 1)) *
				     sizeof(char));
	get_child_path_name(get_path_name(c->path), &child);

	printf("%s\n", child);

	free(child);
}

void
print_subdirectories(directory * dir, container * global) {
	list_node *head = dir->subpaths_c;
	directory *d = NULL;

	if (!has_subdirectories(dir))
		return;
	else
		while (head != NULL) {
			d = (directory *) head->data;
			if (has_value(d->path))
				printf("%s %s\n", get_path_name(d->path),
				       get_path_value(d->path));
			print_subdirectories(d, global);
			head = head->next;
		}
}

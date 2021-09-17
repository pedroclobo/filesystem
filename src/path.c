/*
 * File: path.c
 * Author: Pedro Lobo
 * Description: Path structure related functions.
 */

#include "proj2.h"

/*
 * Create a new path structure,
 * with name and value.
 */
path *
new_path(char *name, char *value) {
	path *new = NULL;

	if (name == NULL)
		return NULL;

	new = (path *) safe_malloc(sizeof(path));

	new->name = (char *) safe_malloc((strlen(name) + 1) * sizeof(char));
	strcpy(new->name, name);

	if (value == NULL)
		new->value = value;
	else {
		new->value =
			(char *) safe_malloc((strlen(value) + 1) *
					     sizeof(char));
		strcpy(new->value, value);
	}

	return new;
}

/*
 * Free path structure from memory.
 */
void
free_path(path * p) {
	if (p) {
		free(p->name);
		free(p->value);
		free(p);
	}
}

/*
 * Determines if a path has an associated value.
 */
int
has_value(path * p) {
	if (p)
		return p->value != NULL;

	return 0;
}

/*
 * If valid, return the path name.
 */
char *
get_path_name(path * p) {
	if (p)
		return p->name;

	return NULL;
}

/*
 * If valid, return the path value.
 */
char *
get_path_value(path * p) {
	if (p)
		if (has_value(p))
			return p->value;

	return NULL;
}

/*
 * Add value to a path. change value of the path.
 * If the path already has a value associated with it,
 * change it if it is valid.
 */
void
add_path_value(path * p, char *value) {
	if (value == NULL)
		return;

	if (has_value(p))
		free(p->value);

	p->value = (char *) safe_malloc((strlen(value) + 1) * sizeof(char));
	strcpy(p->value, value);
}

/*
 * Return the depth of the given path name.
 * Emtpy path names get a depth of 0.
 * Otherwise is corresponds to the number of '/'.
 */
int
get_path_name_depth(char *name) {
	int i, depth = 0;

	for (i = 0; name[i]; i++) {
		if (name[i] == '/')
			depth++;
	}

	return depth;
}

/*
 * Get the parent path name.
 * For path names with a depth of 1, parent is "root".
 */
void
get_parent_path_name(char *name, char **parent) {
	int depth = get_path_name_depth(name), i = 0, s = 0;

	if (depth == 0) {
		*parent = realloc(*parent, strlen("/") + 1);
		strcpy(*parent, "/");
		return;
	}

	else if (depth == 1) {
		*parent = realloc(*parent, strlen("root") + 1);
		strcpy(*parent, "root");
		return;
	}

	while (s < depth) {
		if (name[i] == '/')
			s++;
		(*parent)[i] = name[i];
		i++;
	}
	(*parent)[i - 1] = '\0';
	*parent = realloc(*parent, (i - 1) * sizeof(char));
}

/*
 * Get the child path name.
 * For path names with a depth of 1, child is the path name.
 */
void
get_child_path_name(char *name, char **child) {
	int depth = get_path_name_depth(name), i = 0, s = 0;

	if (depth == 0) {
		free(*child);
		*child = NULL;
		return;
	}

	else if (depth == 1) {
		strcpy(*child, name + 1);
		return;
	}

	while (s < depth) {
		if (name[i] == '/')
			s++;
		i++;
	}

	for (s = 0; name[i]; i++, s++)
		(*child)[s] = name[i];

	(*child)[s] = '\0';
	*child = realloc(*child, s * sizeof(char));
}

/*
 * Trim the existing separators in path names.
 */
void
trim_directory_name(char *name, char **res) {
	char *token = strtok(name, "/");
	strcpy(*res, "/");
	strcat(*res, token);

	while ((token = strtok(NULL, "/"))) {
		strcat(*res, "/");
		strcat(*res, token);
	}
	strcat(*res, "\0");

	*res = realloc(*res, (strlen(*res) + 1) * sizeof(char));
}

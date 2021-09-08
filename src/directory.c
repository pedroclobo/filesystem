#include "proj2.h"

/* Create a new directory */
dir *dir_new(char *path)
{
	int len = strlen(path);
	dir *new = (dir*) malloc(sizeof(dir));

	new->path = (char*) malloc(len * sizeof(char));
	strcpy(new->path, path);
	new->value = NULL;

	new->subpaths_a = NULL;
	new->subpaths_c = NULL;

	return new;
}

/* Add or change value of a directory */
void dir_add_value(dir *d, char *value)
{
	int len = strlen(value);

	if (d->value != NULL)
		free(d->value);

	d->value = (char*) malloc(len * sizeof(char));
	strcpy(d->value, value);
}

/* Get the directory key value */
char *dir_key(void *a)
{
	dir *b = (dir*) a;

	return b->path;
}

/* Directory compare function */
int dir_less(void *a, void *b)
{
	return (strcmp(dir_key(a), dir_key(b)) < 0);
}

/* Directory print function */
void dir_print(void *a)
{
	dir *c = (dir*) a;
	printf("%s\n", c->path);
}

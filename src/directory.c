#include "proj2.h"

/* Create a new directory */
dir *dir_new(char *path)
{
	int len = strlen(path);
	dir *new = (dir*) malloc(sizeof(dir));

	new->path = (char*) malloc(len * sizeof(char));
	strcpy(new->path, path);

	new->subpaths_a = NULL;
	new->subpaths_c = NULL;

	return new;
}

/* Directory compare function */
int dir_less(void *a, void *b)
{
	dir *c = (dir*) a;
	dir *d = (dir*) b;

	return (strcmp(c->path, d->path) < 0);
}

/* Directory print function */
void dir_print(void *a)
{
	dir *c = (dir*) a;
	printf("%s\n", c->path);
}

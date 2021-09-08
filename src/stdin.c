#include "proj2.h"

/* Get a command from the user */
void get_cmd(char **cmd)
{
	int c, i = 0, len = MALLOC_SIZE;

	if (*cmd != NULL)
		free(*cmd);
	*cmd = malloc(MALLOC_SIZE * sizeof(char));

	while ((c = getchar()) != EOF && c != '\n') {
		/* If i becomes equal to malloc size, increase it */
		if (i == len) {
			len += MALLOC_INC;
			*cmd = realloc(*cmd, len);
		}
		(*cmd)[i++] = c;
	}

	/* Realloc to the optimal size */
	*cmd = realloc(*cmd, i * sizeof(char));
	(*cmd)[i] = '\0';
}

/* Return the command flag (ex. "set") */
char *get_cmd_flag(char *cmd)
{
	char *flag = strtok(cmd, " ");

	return flag;
}

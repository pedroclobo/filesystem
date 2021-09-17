/*
 * File: proj1.c
 * Author: Pedro Lobo
 * Description: Command functions.
 */

#include "proj2.h"

/* Print all available commands */
void
help_command() {
	printf("help: %s\n"
	       "quit: %s\n"
	       "set: %s\n"
	       "print: %s\n"
	       "find: %s\n"
	       "list: %s\n"
	       "search: %s\n"
	       "delete: %s\n",
	       DESC_HELP, DESC_QUIT, DESC_SET, DESC_PRINT, DESC_FIND, DESC_LIST,
	       DESC_SEARCH, DESC_DELETE);
}

/*
 * Add or set the value of the directory.
 * If the directory doesn't exists, create it,
 * creating all parent directories too.
 */
void
set_command(char *arguments, container * global) {
	directory *dir = NULL;

	/* Get name and value arguments */
	char *token = strtok(arguments, " \n");
	char *value = strtok(NULL, "\n");
	char *name = NULL;
	if (token == NULL)
		return;
	name = (char *) safe_malloc((strlen(token) + 2) * sizeof(char));

	trim_directory_name(token, &name);

	if (!directory_exists(name, global))
		  add_directory_recursively(name, value, NULL, global);
	else {
		dir = get_directory_by_name(name, global);
		add_directory_value(dir, value);
	}

	free(name);
}

/*
 * Print all directory names and values.
 * Results are search by depth and by order of creation.
 */
void
print_command(container * global) {
	directory *root = get_directory_by_name("root", global);

	print_subdirectories(root, global);
}

/*
 * Print the value of the given directory.
 * If there is no directory with the name given, raise an error.
 * If the directory has no value, raise an error.
 */
void
find_command(char *arguments, container * global) {
	directory *dir = NULL;

	/* Get name argument */
	char *token = strtok(arguments, " \n");
	char *name = (char *) safe_malloc((strlen(token) + 1) * sizeof(char));
	trim_directory_name(token, &name);

	dir = get_directory_by_name(name, global);

	if (dir == NULL)
		printf("%s\n", ERROR_FIND_NOT_FOUND);
	else {
		if (has_value(dir->path))
			printf("%s\n", get_path_value(dir->path));
		else
			printf("%s\n", ERROR_FIND_NO_DATA);
	}

	free(name);
}

/*
 * List all imediate components of a subdirectory.
 */
void
list_command(char *arguments, container * global) {
	directory *dir = get_directory_by_name("root", global);

	/* Get name argument */
	char *token = strtok(arguments, " \n");
	char *name = NULL;

	if (token != NULL) {
		name = (char *) safe_malloc((strlen(token) + 1) * sizeof(char));
		trim_directory_name(token, &name);
		dir = get_directory_by_name(name, global);
	}

	if (dir == NULL)
		printf("%s\n", ERROR_LIST_NOT_FOUND);
	else {
		if (has_subdirectories(dir))
			tree_traverse(dir->subpaths_a, global->print);
	}

	if (token != NULL)
		free(name);
}

void
search_command(char *cmd, container * global) {
	directory *dir = NULL;

	/* Get value argument */
	char *value = strtok(cmd, "\n");

	dir = get_directory_by_value(value, global);

	if (dir == NULL)
		printf("%s\n", ERROR_SEARCH_NOT_FOUND);
	else
		printf("%s\n", get_path_name(dir->path));
}

void
delete_command(char *arguments, container * global) {
	directory *dir = NULL;

	/* Get name and value arguments */
	char *token = strtok(arguments, " \n");
	char *name = NULL;

	if (token == NULL)
		remove_all_directories(global);
	else {
		name = (char *) safe_malloc((strlen(token) + 2) * sizeof(char));
		trim_directory_name(token, &name);
		dir = get_directory_by_name(name, global);
		remove_directory_recursively(dir, global);
	}

	free(name);
}

/*
 * Get the corresponding command arguments.
 * Return 1 if the command invoked isn't the quit command.
 * Return 0 otherwise.
 */
int
parse_command(char *cmd, container * global) {
	int result = 1;
	char *cmd_flag = NULL;

	/* Get command from user */
	cmd = fgets(cmd, MAX_CMD_SIZE, stdin);
	if (cmd == NULL)
		return 1;

	cmd_flag = strtok(cmd, WHITESPACE);

	if (cmd_flag != NULL) {
		if (!strcmp(cmd_flag, "help"))
			help_command();
		else if (!strcmp(cmd_flag, "quit"))
			result = 0;
		else if (!strcmp(cmd_flag, "set"))
			set_command(cmd + strlen(cmd_flag) + 1, global);
		else if (!strcmp(cmd_flag, "print"))
			print_command(global);
		else if (!strcmp(cmd_flag, "find"))
			find_command(cmd + strlen(cmd_flag) + 1, global);
		else if (!strcmp(cmd_flag, "list"))
			list_command(cmd + strlen(cmd_flag) + 1, global);
		else if (!strcmp(cmd_flag, "search"))
			search_command(cmd + strlen(cmd_flag) + 1, global);
		else if (!strcmp(cmd_flag, "delete"))
			delete_command(cmd + strlen(cmd_flag) + 1, global);
	}

	return result;
}

int
main() {
	char *cmd = (char *) safe_malloc(MAX_CMD_SIZE * sizeof(char));
	container global;
	init_container(&global);

	while (parse_command(cmd, &global));

	free_container(&global);
	free(cmd);

	return 0;
}

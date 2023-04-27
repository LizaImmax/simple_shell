#include "simple_shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **args)
{
	char *error, *hist_command;
	int a;

	hist_command = _itoa(hist);
	if (!hist_command)
		return (NULL);

	a = _strlen(name) + _strlen(hist_command) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (a + 1));
	if (!error)
	{
		free(hist_command);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_command);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_command);
	return (error);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **args)
{
	char *error, *hist_command;
	int p;

	hist_command = _itoa(hist);
	if (!hist_command)
		return (NULL);

	p = _strlen(name) + _strlen(hist_command) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (p + 1));
	if (!error)
	{
		free(hist_command);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_command);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_command);
	return (error);
}

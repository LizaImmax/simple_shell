#include "simple_shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **args)
{
	char *error, *hist_command;
	int len;

	hist_command = _itoa(hist);
	if (!hist_command)
		return (NULL);

	args--;
	n = _strlen(name) + _strlen(hist_command) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (n + 1));
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
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_command);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **args)
{
	char *error;
	int length;

	length = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **args)
{
	char *error, *hist_command;
	int b;

	hist_command = _itoa(hist);
	if (!hist_command)
		return (NULL);

	b = _strlen(name) + _strlen(hist_command) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (b + 1));
	if (!error)
	{
		free(hist_command);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_command);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_command);
	return (error);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_cd(char **args)
{
	char *error, *hist_command;
	int j;

	hist_command = _itoa(hist);
	if (!hist_command)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	j = _strlen(name) + _strlen(hist_command) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (j + 1));
	if (!error)
	{
		free(hist_command);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_command);
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_command);
	return (error);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **args)
{
	char *error, *hist_command;
	int k;

	hist_command = _itoa(hist);
	if (!hist_command)
		return (NULL);

	k = _strlen(name) + _strlen(hist_command) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (k + 1));
	if (!error)
	{
		free(hist_command);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_command);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_command);
	return (error);
}

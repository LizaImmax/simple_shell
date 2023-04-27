#include "shell.h"

/**
 * path_cmd -  search path
 * @cmd: command
 * Return: 1  Failure  0  Success.
 */
int path_cmd(char **cmd)
{
	char *path, *value, *cmd_path;
	struct stat buf;

	path = _getenv("PATH");
	value = _strtok(path, ":");
	while (value != NULL)
	{
		cmd_path = build(*cmd, value);
		if (stat(cmd_path, &buf) == 0)
		{
			*cmd = _strdup(cmd_path);
			free(cmd_path);
			free(path);
			return (0);
		}
		free(cmd_path);
		value = _strtok(NULL, ":");
	}
	free(path);

	return (1);
}
/**
 * build - Build Command
 * @token: Excute Command
 * @value: Dirctory Conatining Command
 *
 * Return: path
 */
char *build(char *token, char *value)
{
	char *cmd;
	size_t length;

	length = _strlen(value) + _strlen(token) + 2;
	cmd = malloc(sizeof(char) * length);
	if (cmd == NULL)
	{
		return (NULL);
	}

	memset(cmd, 0, length);

	cmd = _strcat(cmd, value);
	cmd = _strcat(cmd, "/");
	cmd = _strcat(cmd, token);

	return (cmd);
}
/**
 * _getenv - get environment
 * @name: Environment Variable Name
 * Return: The Value of the Environment Variable Else NULL.
 */
char *_getenv(char *name)
{
	size_t nul, val;
	char *value;
	int i, x, j;

	nul = _strlen(name);
	for (i = 0 ; environ[i]; i++)
	{
		if (_strncmp(name, environ[i], nul) == 0)
		{
			val = _strlen(environ[i]) - nul;
			value = malloc(sizeof(char) * val);
			if (!value)
			{
				free(value);
				perror("unable to alloc");
				return (NULL);
			}

			j = 0;
			for (x = nul + 1; environ[i][x]; x++, j++)
			{
				value[j] = environ[i][x];
			}
			value[j] = '\0';

			return (value);
		}
	}

	return (NULL);
}

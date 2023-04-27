#include "simple_shell.h"


void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t d;

	for (d = 0; args[d] || args[d + 1]; d++)
		free(args[d]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buff;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(file);
		return (NULL);
	}
	read(file, buff, 120);
	while (buff[i] != ' ')
		i++;
	buff[i] = '\0';

	close(file);
	return (buff);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *m, *r;

	r = malloc(len + 1);
	if (!r)
		return (NULL);
	r[0] = '\0';
	_strncat(r, beginning, len);

	var_addr = _getenv(r);
	free(r);
	if (var_addr)
	{
		m = *var_addr;
		while (*m != '=')
			m++;
		m++;
		replacement = malloc(_strlen(m) + 1);
		if (replacement)
			_strcpy(replacement, m);
	}

	return (replacement);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int p, k = 0, n;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (p = 0; old_line[p]; p++)
	{
		if (old_line[p] == '$' && old_line[p + 1] &&
				old_line[p + 1] != ' ')
		{
			if (old_line[p + 1] == '$')
			{
				replacement = get_pid();
				k = p + 2;
			}
			else if (old_line[p + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = p + 2;
			}
			else if (old_line[p + 1])
			{
				/* extract the variable name to search for */
				for (k = p + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				n = k - (p + 1);
				replacement = get_env_value(&old_line[p + 1], n);
			}
			new_line = malloc(p + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, p);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			p = -1;
		}
	}
}

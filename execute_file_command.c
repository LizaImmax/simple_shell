#include "shell.h"
/**
 * read_file - get command from file
 * @filename: filename
 * @argv: argument
 * Return: void
 */

void read_file(char *filename, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t length = 0;
	int count = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while ((getline(&line, &length, fp)) != -1)
	{
		count++;
		treat_file(line, count, fp, argv);

	}
	if (line)
		free(line);
	fclose(fp);
	exit(0);
}
/**
 * treat_file - check command
 * @line: file line
 * @counter: counter
 * @fp:File Descriptor
 * @argv: argument
 * Return : void
 */
void treat_file(char *line, int counter, FILE *fp, char **argv)
{
	char **cmd;
	int strt = 0;

	cmd = parse_cmd(line);

		if (_strncmp(cmd[0], "exit", 4) == 0)
		{
			exit_bul_for_file(cmd, line, fp);
		}
		else if (check_builtin(cmd) == 0)
		{
			strt = handle_builtin(cmd, strt);
			free(cmd);
		}
		else
		{
			strt = check_cmd(cmd, line, counter, argv);
			free(cmd);
		}
}
/**
 * exit_bul_for_file - exit file
 * @line: file line
 * @cmd: command
 * @fd:File Descriptor
 * Return : exit case
 */
void exit_bul_for_file(char **cmd, char *line, FILE *fd)
{
	int state, k = 0;

	if (cmd[1] == NULL)
	{
		free(line);
		free(cmd);
		fclose(fd);
		exit(errno);
	}
	while (cmd[1][k])
	{
		if (_isalpha(cmd[1][k++]) < 0)
		{
			perror("illegal number");
		}
	}
	state = _atoi(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(state);



}

/**
 * check_delim - check delimeter
 * @c: char
 * @str: string
 * Return: 0
 */
unsigned int check_delim(char c, const char *str)
{
	unsigned int x;

	for (x = 0; str[x] != '\0'; x++)
	{
		if (c == str[x])
			return (1);
	}
	return (0);
}


/**
 * _strtok - string token
 * @str: String
 * @delim: Delimiter
 * Return: Token pointer
 */
char *_strtok(char *str, const char *delim)
{
	static char *p;
	static char *q;
	unsigned int i;

	if (str != NULL)
		q = str;
	p = q;
	if (p == NULL)
		return (NULL);
	for (i = 0; p[i] != '\0'; i++)
	{
		if (check_delim(p[i], delim) == 0)
			break;
	}
	if (q[i] == '\0' || q[i] == '#')
	{
		q = NULL;
		return (NULL);
	}
	p = q + i;
	p = p;
	for (i = 0; q[i] != '\0'; i++)
	{
		if (check_delim(q[i], delim) == 1)
			break;
	}
	if (q[i] == '\0')
		q = NULL;
	else
	{
		q[i] = '\0';
		q = q + i + 1;
		if (*q == '\0')
			q = NULL;
	}
	return (p);
}

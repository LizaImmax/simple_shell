#include "shell.h"

/**
 * prompt - Display Shell Prompt
 */
void prompt(void)
{
	PRINTER("$ ");
}
/**
 * print_error - print error
 * @input:User input
 * @counter:Simple Shell Count Loop
 * @argv: argument
 * Return: Void
 */
void print_error(char *input, int counter, char **argv)
{
	char *err;

	PRINTER(argv[0]);
	PRINTER(": ");
	err = _itoa(counter);
	PRINTER(err);
	free(err);
	PRINTER(": ");
	PRINTER(input);
	PRINTER(": not found\n");
}


/**
 * history_dis - command history
 * @c:Parsed Command
 * @s:Status of last command
 * Return: 0 or -1
 */
int history_dis(__attribute__((unused))char **c, __attribute__((unused))int s)
{
	char *filename = ".simple_shell_history";
	FILE *fp;
	char *line = NULL;
	size_t length = 0;
	int count = 0;
	char *err;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return (-1);
	}
	while ((getline(&line, &length, fp)) != -1)
	{
		count++;
		err = _itoa(count);
		PRINTER(err);
		free(err);
		PRINTER(" ");
		PRINTER(line);

	}
	if (line)
		free(line);
	fclose(fp);
	return (0);
}
/**
 * print_echo - for echo
 * @cmd: command
 * Return: 0 or -1
 */
int print_echo(char **cmd)
{
	pid_t pid;
	int stat;

	pid = fork();
	if (pid == 0)
	{
	if (execve("/bin/echo", cmd, environ) == -1)
	{
		return (-1);
	}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		return (-1);
	}
	else
	{
		do {
			waitpid(pid, &stat, WUNTRACED);
		} while (!WIFEXITED(stat) && !WIFSIGNALED(stat));
	}
	return (1);
}

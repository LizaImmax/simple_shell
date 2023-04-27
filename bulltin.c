#include "shell.h"
/**
 * exit_bul - exit shell
 * @cmd: Command
 * @input: Input
 * @argv: argument
 * @c: Count
 * Return: Void
 */
void  exit_bul(char **cmd, char *input, char **argv, int c)
{
	int stat, i = 0;

	if (cmd[1] == NULL)
	{
		free(input);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	while (cmd[1][i])
	{
		if (_isalpha(cmd[1][i++]) != 0)
		{
			_prerror(argv, c, cmd);
			break;
		}
		else
		{
			stat = _atoi(cmd[1]);
			free(input);
			free(cmd);
			exit(stat);
		}
	}
}


/**
 * change_dir - Change Dirctorie
 * @cmd: Command
 * @er: counter
 * Return: 0
 */
int change_dir(char **cmd, __attribute__((unused))int er)
{
	int val = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		val = chdir(getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		val = chdir(getenv("OLDPWD"));
	}
	else
		val = chdir(cmd[1]);

	if (val == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (val != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
/**
 * dis_env - display env
 * @cmd:command
 * @er: last comm
 * Return:Always 0
 */
int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int er)
{
size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = _strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
 * display_help - help
 * @cmd: command
 * @er: status
 * Return: 0
 */
int display_help(char **cmd, __attribute__((unused))int er)
{
	int fdoc, fw, rd = 1;
	char t;

	fdoc = open(cmd[1], O_RDONLY);
	if (fdoc < 0)
	{
		perror("Error");
		return (0);
	}
	while (rd > 0)
	{
		rd = read(fdoc, &t, 1);
		fw = write(STDOUT_FILENO, &t, rd);
		if (fw < 0)
		{
			return (-1);
		}
	}
	_putchar('\n');
	return (0);
}
/**
 * echo_bul - echo command
 * @st: status
 * @cmd: command
 * Return: 0
 */
int echo_bul(char **cmd, int st)
{
	char *path;
	unsigned int  pid = getppid();

	if (_strncmp(cmd[1], "$?", 2) == 0)
	{
		print_number_in(st);
		PRINTER("\n");
	}
	else if (_strncmp(cmd[1], "$$", 2) == 0)
	{
		print_number(pid);
		PRINTER("\n");

	}
	else if (_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = _getenv("PATH");
		PRINTER(path);
		PRINTER("\n");
		free(path);

	}
	else
		return (print_echo(cmd));

	return (1);
}

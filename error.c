#include "shell.h"
/**
 *  _prerror - printing error
 * @argv: argument
 * @c: counter
 * @cmd: command
 * Return: Void
 */
void _prerror(char **argv, int c, char **cmd)
{
	char *err = _itoa(c);

	PRINTER(argv[0]);
	PRINTER(": ");
	PRINTER(err);
	PRINTER(": ");
	PRINTER(cmd[0]);
	PRINTER(": Illegal number: ");
	PRINTER(cmd[1]);
	PRINTER("\n");
	free(err);
}

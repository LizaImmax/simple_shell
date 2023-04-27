#include "simple_shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int k;
	int length = 1;

	if (num < 0)
	{
		length++;
		k = num * -1;
	}
	else
	{
		k = num;
	}
	while (k > 9)
	{
		length++;
		k /= 10;
	}

	return (length);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int length = num_length(num);
	unsigned int i;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		i = num * -1;
		buffer[0] = '-';
	}
	else
	{
		i = num;
	}

	length--;
	do {
		buffer[length] = (i % 10) + '0';
		i /= 10;
		length--;
	} while (i > 0);

	return (buffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *error_name;

	switch (err)
	{
	case -1:
		error_name = error_env(args);
		break;
	case 1:
		error_name = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error_name = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error_name = error_2_syntax(args);
		else
			error_name = error_2_cd(args);
		break;
	case 126:
		error_name = error_126(args);
		break;
	case 127:
		error_name = error_127(args);
		break;
	}
	write(STDERR_FILENO, error_name, _strlen(error));

	if (error_name)
		free(error_name);
	return (err);

}

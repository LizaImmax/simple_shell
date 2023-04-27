#include "shell.h"

/**
* _getline - Read user input
* Return: Input
*/
char *_getline()
{
int i, buffsize = BUFSIZE, reader;
char count = 0;
char *buff = malloc(buffsize);

	if (buff == NULL)
	{
		free(buff);
		return (NULL);
	}

	for (i = 0; count != EOF && count != '\n'; i++)
	{
		fflush(stdin);
		reader = read(STDIN_FILENO, &count, 1);
		if (reader == 0)
		{
			free(buff);
			exit(EXIT_SUCCESS);
		}
		buff[i] = count;
		if (buff[0] == '\n')
		{
			free(buff);
			return ("\0");
		}
		if (i >= buffsize)
		{
			buff = _realloc(buff, buffsize, buffsize + 1);
			if (buff == NULL)
			{
				return (NULL);
			}
		}
	}
	buff[i] = '\0';
	hashtag_handle(buff);
	return (buff);
}

/**
 * hashtag_handle - handle comment
 * @buff: input;
 * Return:void
 */
void hashtag_handle(char *buff)
{
	int i;

		for (i = 0; buff[i] != '\0'; i++)
		{
			if (buff[i] == '#')
			{
			buff[i] = '\0';
			break;
			}
	}
}


/**
 * history - Fill File By User Input
 * @input: User Input
 * Return: -1 Fail 0 Succes
 */
int history(char *input)
{
	char *filename = ".simple_shell_history";
	ssize_t fdoc, w;
	int length = 0;

	if (!filename)
		return (-1);
	fdoc = open(filename, O_CREAT | O_RDWR | O_APPEND, 00600);
	if (fdoc < 0)
		return (-1);
	if (input)
	{
		while (input[length])
			length++;
		w = write(fdoc, input, length);
		if (w < 0)
			return (-1);
	}
	return (1);
}
/**
 * free_env - Free env.
 * @env:  Environment.
 * Return: Void
 */
void free_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		free(env[i]);
	}
}


/**
 * parse_cmd - Parse command
 * @input: command
 * Return: array of the character
 */
char **parse_cmd(char *input)
{
	char **tokens;
	char *token;
	int i, buffsize = BUFSIZE;

	if (input == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * buffsize);
	if (!tokens)
	{
		perror("hsh");
		return (NULL);
	}

	token = _strtok(input, "\n ");
	for (i = 0; token; i++)
	{
		tokens[i] = token;
		token = _strtok(NULL, "\n ");
	}
	tokens[i] = NULL;

	return (tokens);
}

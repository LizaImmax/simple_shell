#include "simple_shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char p, c, n;
	size_t i, j;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		c = old_line[i];
		n = old_line[i + 1];
		if (i != 0)
		{
			p = old_line[i - 1];
			if (c == ';')
			{
				if (n == ';' && p != ' ' && p != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (p == ';' && n != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (p != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (n != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (c == '&')
			{
				if (n == '&' && p != ' ')
					new_line[j++] = ' ';
				else if (p == '&' && n != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (c == '|')
			{
				if (n == '|' && p != ' ')
					new_line[j++]  = ' ';
				else if (p == '|' && n != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (c == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (n != ' ' && n != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char c, n;

	for (i = 0; line[i]; i++)
	{
		c = line[i];
		n = line[i + 1];
		if (c == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (c == ';')
			{
				if (n == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && n != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[i], &new_len);
		}
		else if (c == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (n != ' ' && n != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char p, c, n;

	p = *(line - 1);
	c = *line;
	n = *(line + 1);

	if (c == '&')
	{
		if (n == '&' && p != ' ')
			(*new_len)++;
		else if (p == '&' && n != ' ')
			(*new_len)++;
	}
	else if (c == '|')
	{
		if (n == '|' && p != ' ')
			(*new_len)++;
		else if (p == '|' && n != ' ')
			(*new_len)++;
	}
}

#include "simple_shell.h"

void insert_spaces(char *old_line, char *new_line);
void free_line(char **line);
void operations(char *line, ssize_t *new_length);
ssize_t newer_length(char *line);
void line_handler(char **line, ssize_t read);

/**
 * insert_spaces - inserts spaces and spacial characters.
 * @old_line: A pointer to th precious line.
 * @new_line: new line.
 */

void insert_spaces(char *old_line, char *new_line)
{
	char previous, current, next;
	size_t i, j = 0;

	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				} else if (previous == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			} else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			} else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		} else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';
}
/**
* free_line - frees line after use
* @line: line to be freed
*/
void free_line(char **line)
{
	free(*line);
	*line = NULL;
}
/**
* line_handler - reads line from standard input
* @line: line to handle
* @read: read the line
*/

void line_handler(char **line, ssize_t read)
{
	char *old_line, *new_line;
	size_t new_len;

	new_len = newer_length(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	old_line = *line;

	insert_spaces(old_line, new_line);

	free_line(line);
	*line = new_line;
}

/**
 * newer_length - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t newer_length(char *line)
{
	size_t i;
	ssize_t new_length = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_length++;
				if (next != ' ')
					new_length++;
			}
			else
				operations(&line[i], &new_length);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_length++;
			if (next != ' ' && next != ';')
				new_length++;
		}
		new_length++;
	}
	return (new_length);
}
/**
 * operations - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_length: Pointer to new_len in get_new_len function.
 */
void operations(char *line, ssize_t *new_length)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_length)++;
		else if (previous == '&' && next != ' ')
			(*new_length)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_length)++;
		else if (previous == '|' && next != ' ')
			(*new_length)++;
	}
}

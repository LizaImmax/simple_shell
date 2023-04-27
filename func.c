#include "shell.h"
/**
 * _strcpy - copy stry
 * @dest: destination
 * @src: source
 * Return: pointer to copied str
 */
char *_strcpy(char *dest, char *src)
{
int i;

i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
dest[i] = '\0';
return (dest);
}

/**
 * _strcat - combine strings
 * @dest:First String
 * @src:Second String
 * Return:First String + Second String pointer
 */
char *_strcat(char *dest, char *src)
{
	char *to = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (to);
}
/**
 * _strchr - get char in a string
 * @s: String
 * @c: Char
 * Return: Pointer To Char*
 */
char *_strchr(char *s, char c)
{

	do		{

		if (*s == c)
			{
			break;
			}
		}	while (*s++);

return (s);
}
/**
 * _strncmp - compare strings.
 * @s1: String 1.
 * @s2: String 2.
 * @n: number Of Characters To Compare.
 *
 * Return: 0
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t j;

	if (s1 == NULL)
		return (-1);
	for (j = 0; j < n && s2[j]; j++)
	{
		if (s1[j] != s2[j])
		{
			return (1);
		}
	}
	return (0);
}
/**
 * _strdup - dup string
 * @str: string
 * Return: duplicate
 */
char *_strdup(char *str)
{
	size_t length, i;
	char *str2;

	length = _strlen(str);
	str2 = malloc(sizeof(char) * (length + 1));
	if (!str2)
	{
		return (NULL);
	}

	for (i = 0; i <= length; i++)
	{
		str2[i] = str[i];
	}

	return (str2);
}

#include "shell.h"

/**
 * _strcmp - compare two strings
 * @s1:String 1
 * @s2:String 2
 * Return: 0 or difference
 */
int _strcmp(char *s1, char *s2)
{
int cmp = 0, j, len1, len2;
len1 = _strlen(s1);
len2 = _strlen(s2);

	if (s1 == NULL || s2 == NULL)
		return (1);
	if (len1 != len2)
		return (1);
	for (j = 0; s1[j]; j++)
	{
		if (s1[j] != s2[j])
		{
			cmp = s1[j] - s2[j];
			break;
		}
		else
			continue;
	}
	return (cmp);
}
/**
 * _isalpha - check if alphabet
 *@c: Character
 * Return: 0 or 1
 */
int _isalpha(int c)
{
	if (((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/**
 * _itoa - convert int to char
 * @n: Int To Convert
 * Return: Char Pointer
 */
char *_itoa(unsigned int n)
{
	int len = 0, i = 0;
	char *d;

	len = intlen(n);
	d = malloc(len + 1);
	if (!d)
		return (NULL);
	*d = '\0';
	while (n / 10)
	{
		d[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	d[i] = (n % 10) + '0';
	array_rev(d, len);
	d[i + 1] = '\0';
	return (d);
}

/**
 *  array_rev - reverse array
 * @arr: array to rev
 * @len: array length
 * Return: reversed array
 */
void array_rev(char *arr, int len)
{
	int a;
	char tmp;

	for (a = 0; a < (len / 2); a++)
	{
		tmp = arr[a];
		arr[a] = arr[(len - 1) - a];
		arr[(len - 1) - a] = tmp;
	}
}

/**
 * intlen - get len of an int
 * @num: int
 * Return: length
 */
int intlen(int num)
{
	int len = 0;

	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

#include "shell.h"

/**
 * str_length - returns the length of a string.
 * @string: pointer to string.
 * Return: length of string.
 */
int str_length(char *string)
{
	if (string == NULL)
		return (0);

	int length = 0;

	while (string[length] != '\0')
	{
		length++;
	}
	return (length);
}

/**
 * str_duplicate - duplicates a string
 * @string: String to be copied
 * Return: pointer to the duplicated string
 */
char *str_duplicate(char *string)
{
	if (string == NULL)
		return (NULL);

	int length = str_length(string) + 1;
	char *result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		perror("Error");
		return (NULL);
	}

	for (int i = 0; i < length; i++)
	{
		result[i] = string[i];
	}

	return (result);
}

/**
 * str_compare - Compare two strings
 * @string1: String one
 * @string2: String two
 * @number: number of characters to be compared, 0 for infinite
 * Return: 1 if the strings are equal, 0 if different
 */
int str_compare(char *string1, char *string2, int number)
{
	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		while (*string1 != '\0' && *string2 != '\0')
		{
			if (*string1 != *string2)
				return (0);
			string1++;
			string2++;
		}
		return (*string1 == *string2);
	}
	else
	{
		for (int i = 0; i < number; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
}

/**
 * str_concat - concatenates two strings.
 * @string1: String to be concatenated
 * @string2: String to be concatenated
 * Return: pointer to the concatenated string
 */
char *str_concat(char *string1, char *string2)
{
	if (string1 == NULL)
		string1 = "";
	if (string2 == NULL)
		string2 = "";

	int length1 = str_length(string1);
	int length2 = str_length(string2);

	char *result = malloc(sizeof(char) * (length1 + length2 + 1));

	if (result == NULL)
	{
		perror("Error");
		return (NULL);
	}

	for (int i = 0; i < length1; i++)
	{
		result[i] = string1[i];
	}

	for (int i = 0; i < length2; i++)
	{
		result[length1 + i] = string2[i];
	}

	result[length1 + length2] = '\0';
	return (result);
}

/**
 * str_reverse - reverses a string.
 * @string: pointer to string.
 * Return: void.
 */
void str_reverse(char *string)
{
	if (string == NULL)
		return;

	int length = str_length(string);
	int i = 0;

	while (i < length / 2)
	{
		char temp = string[i];

		string[i] = string[length - i - 1];
		string[length - i - 1] = temp;
		i++;
	}
}

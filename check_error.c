#include "main.h"

/**
 * repetition_char - counts  repetitions character
 * @input: string
 * @i: index
 * Return: show the repetitions
 */
int repetition_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repetition_char(input - 1, i + 1));

	return (i);
}

/**
 * syn_error - display syntax errors
 * @input: input str
 * @i: index
 * @last: final char read
 * Return: index of error. 0 when there are no
 * errors
 */
int syn_error(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (syn_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repetition_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repetition_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (syn_error(input + 1, i + 1, *input));
}

/**
 * first_ind_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_ind_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_err - prints when a syntax error is found
 *
 * @darel: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control message error
 * Return: no return
 */
void print_syntax_err(list_ti *darel, char *input, int i, int bool)
{
	char *meesg, *meesg2, *meesg3, *error, *counter;
	int lengthes;

	if (input[i] == ';')
	{
		if (bool == 0)
			meesg = (input[i + 1] == ';' ? ";;" : ";");
		else
			meesg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		meesg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		meesg = (input[i + 1] == '&' ? "&&" : "&");

	meesg2 = ": Syntax error: \"";
	meesg3 = "\" unexpected\n";
	counter = conv_itst(darel->counter);
	lengthes = _strlen(darel->av[0]) + _strlen(counter);
	lengthes += _strlen(meesg) + _strlen(meesg2) + _strlen(meesg3) + 2;

	error = malloc(sizeof(char) * (lengthes + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, darel->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, meesg2);
	_strcat(error, meesg);
	_strcat(error, meesg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, lengthes);
	free(error);
	free(counter);
}

/**
 * check_syntax_err - intermediate function to
 * find and print a syntax error
 *
 * @darel: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_err(list_ti *darel, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_ind_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_err(darel, input, begin, 0);
		return (1);
	}

	i = syn_error(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_err(darel, input, begin + i, 1);
		return (1);
	}

	return (0);
}

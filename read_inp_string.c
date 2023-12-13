#include "main.h"

/**
 * read_inp_string - Read inpt from stream
 * @i_eof : stream to read from
 * Return: The number of bytes
 */
char *read_inp_string(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}

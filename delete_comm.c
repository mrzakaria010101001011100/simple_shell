#include "main.h"

/**
 * delete_comment - deletes comment
 * @in: input str
 * Return: return input
 */
char *delete_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _reallocmemo(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * loop_shell - display Loop shell
 * @darel: av, input, args
 * Return: return if there is no return.
 */
void loop_shell(list_ti *darel)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_inp_string(&i_eof);
		if (i_eof != -1)
		{
			input = delete_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_err(darel, input) == 1)
			{
				darel->status = 2;
				free(input);
				continue;
			}
			input = replace_variable(input, darel);
			loop = split_cmd(darel, input);
			darel->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

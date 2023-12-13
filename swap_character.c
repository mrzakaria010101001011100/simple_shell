#include "main.h"

/**
 * swap_character - swaps | and & for non-printed chars
 * @input: input string
 * @bool: type of swap
 * Return: swap string
 */
char *swap_character(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_separatenodes - add separators and command lines in the lists
 * @head_s: head of separator
 * @head_l: head of command list
 * @input: input string
 * Return: show if there is no return
 */
void add_separatenodes(head_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_character(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			separate_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			separate_end(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_character(line, 1);
		command_node(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_nextcmd - next command line stored
 * @list_s: separator list
 * @list_l: command line list
 * @darel: data structure
 * Return: show if there is no return
 */
void go_nextcmd(head_list **list_s, line_list **list_l, list_ti *darel)
{
	int loop_sep;
	head_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (darel->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_cmd - splits the command lines according to
 * the separators
 * @darel: data structure
 * @input: input string
 * Return: return 0 to exit otherwise 1 to continue
 */
int split_cmd(list_ti *darel, char *input)
{

	head_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_separatenodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		darel->input = list_l->line;
		darel->args = split_line(darel->input);
		loop = exec_line_command(darel);
		free(darel->args);

		if (loop == 0)
			break;

		go_nextcmd(&list_s, &list_l, darel);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	separator_list(&head_s);
	f_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes input string
 * @input: input string.
 * Return: string splitted
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _redou(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

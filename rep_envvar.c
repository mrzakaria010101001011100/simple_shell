#include "main.h"

/**
 * check_env_var -  typed variable is an enviroment variable
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: show if there is no return
 */
void check_env_var(r_var **h, char *in, list_ti *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				addvar_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	addvar_node(h, j, NULL, 0);
}

/**
 * check_Tvariables -  typed variable is $$ or $?
 * @h: header linked list
 * @in: input string
 * @st: last status of Shell
 * @data: data structure
 * Return: show if there is no return
 */
int check_Tvariables(r_var **h, char *in, char *st, list_ti *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				addvar_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				addvar_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				addvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				addvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				addvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				addvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				addvar_node(h, 0, NULL, 0);
			else
				check_env_var(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaces_stinput - replaces string into variables
 * @head: header linked list
 * @input: input string
 * @new_input: new input
 * @nlen: new length
 * Return: replaced string
 */
char *replaces_stinput(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * replace_variable - replace string into variable
 * @input: input string
 * @darel: data structure
 * Return: replaced string
 */
char *replace_variable(char *input, list_ti *darel)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = conv_itst(darel->status);
	head = NULL;

	olen = check_Tvariables(&head, input, status, darel);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaces_stinput(&head, input, new_input, nlen);

	free(input);
	free(status);
	rvariable_list(&head);

	return (new_input);
}

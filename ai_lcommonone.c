#include "main.h"

/**
 * addvar_node - adding variable at the last
 * r_var list.
 * @head: header linked list.
 * @lvar: show the length variable.
 * @val: the value variable.
 * @lval: the length value.
 * Return: the address head.
 */
r_var *addvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * rvariable_list - show frees  r_var list
 * @head: header linked list.
 * Return: show if there is no return.
 */
void rvariable_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

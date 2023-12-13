#include "main.h"

/**
 * separate_end - separator found at last
 * head
 * @head: header linked list
 * @sep: separator found
 * Return: address head.
 */
head_list *separate_end(head_list **head, char sep)
{
	head_list *new, *temp;

	new = malloc(sizeof(head_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
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
 * separator_list - frees a head listing
 * @head: head linked list.
 * Return: show if there is no return.
 */
void separator_list(head_list **head)
{
	head_list *temp;
	head_list *curr;

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

/**
 * command_node -  command line at the last
 * linelist
 * @head: header linked list.
 * @line: command line.
 * Return: address the head section
 */
line_list *command_node(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
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
 * f_line_list - free the main line_list
 * @head: header linked list.
 * Return: show if there is no return.
 */
void f_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

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

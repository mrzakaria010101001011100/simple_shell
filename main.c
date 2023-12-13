#include "main.h"

/**
 * free_data - frees data structure
 *
 * @darel: data structure
 * Return: no return
 */
void free_data(list_ti *darel)
{
	unsigned int i;

	for (i = 0; darel->_environ[i]; i++)
	{
		free(darel->_environ[i]);
	}

	free(darel->_environ);
	free(darel->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @darel: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(list_ti *darel, char **av)
{
	unsigned int i;

	darel->av = av;
	darel->input = NULL;
	darel->args = NULL;
	darel->status = 0;
	darel->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	darel->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		darel->_environ[i] = _dupheapmemo(environ[i]);
	}

	darel->_environ[i] = NULL;
	darel->pid = conv_itst(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	list_ti darel;
	(void) ac;

	signal(SIGINT, get_prompt);
	set_data(&darel, av);
	loop_shell(&darel);
	free_data(&darel);
	if (darel.status < 0)
		return (255);
	return (darel.status);
}


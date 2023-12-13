#include "main.h"

/**
 * exec_line_command - finds the builtin
 * @darel: args
 * Return: 1 on success.
 */
int exec_line_command(list_ti *darel)
{
	int (*builtin)(list_ti *darel);

	if (darel->args[0] == NULL)
		return (1);

	builtin = builtin_cmd(darel->args[0]);

	if (builtin != NULL)
		return (builtin(darel));

	return (cmd_execute(darel));
}

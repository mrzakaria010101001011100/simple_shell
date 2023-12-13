#include "main.h"

/**
 * getc_error - calls the error builtin
 * @darel: display the data structure
 * @eval: error value
 * Return: show if thereis any error
 */
int getc_error(list_ti *darel, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env_message(darel);
		break;
	case 126:
		error = error_path(darel);
		break;
	case 127:
		error = error_not_Messagefound(darel);
		break;
	case 2:
		if (_strcmp("exit", darel->args[0]) == 0)
			error = error_exit_message(darel);
		else if (_strcmp("cd", darel->args[0]) == 0)
			error = error_get_directory(darel);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	darel->status = eval;
	return (eval);
}

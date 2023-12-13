#include "main.h"

/**
 * error_env_message - error message for env in get_env.
 * @darel: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env_message(data_shell *darel)
{
	int lengthes;
	char *error;
	char *v_str;
	char *meesg;

	v_str = conv_itst(darel->counter);
	meesg = ": Unable to add/remove from environment\n";
	lengthes = _strlen(darel->av[0]) + _strlen(v_str);
	lengthes += _strlen(darel->args[0]) + _strlen(meesg) + 4;
	error = malloc(sizeof(char) * (lengthes + 1));
	if (error == 0)
	{
		free(error);
		free(v_str);
		return (NULL);
	}

	_strcpy(error, darel->av[0]);
	_strcat(error, ": ");
	_strcat(error, v_str);
	_strcat(error, ": ");
	_strcat(error, darel->args[0]);
	_strcat(error, meesg);
	_strcat(error, "\0");
	free(v_str);

	return (error);
}
/**
 * error_path - error message for path and failure denied permission.
 * @darel: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path(data_shell *darel)
{
	int lengthes;
	char *v_str;
	char *error;

	v_str = conv_itst(darel->counter);
	lengthes = _strlen(darel->av[0]) + _strlen(v_str);
	lengthes += _strlen(darel->args[0]) + 24;
	error = malloc(sizeof(char) * (lengthes + 1));
	if (error == 0)
	{
		free(error);
		free(v_str);
		return (NULL);
	}
	_strcpy(error, darel->av[0]);
	_strcat(error, ": ");
	_strcat(error, v_str);
	_strcat(error, ": ");
	_strcat(error, darel->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(v_str);
	return (error);
}


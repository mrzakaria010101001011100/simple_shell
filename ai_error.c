#include "main.h"

/**
 * st_con - function that concatenates the message for cd error
 *
 * @darel: data relevant to the directory
 * @meesg: message output
 * @error: error display message
 * @v_str: counter message to show the line
 * Return: show if there is any error message
 */
char *st_con(list_ti *darel, char *meesg, char *error, char *v_str)
{
	char *sgn_flag;

	_strcpy(error, darel->av[0]);
	_strcat(error, ": ");
	_strcat(error, v_str);
	_strcat(error, ": ");
	_strcat(error, darel->args[0]);
	_strcat(error, meesg);
	if (darel->args[1][0] == '-')
	{
		sgn_flag = malloc(3);
		sgn_flag[0] = '-';
		sgn_flag[1] = darel->args[1][1];
		sgn_flag[2] = '\0';
		_strcat(error, sgn_flag);
		free(sgn_flag);
	}
	else
	{
		_strcat(error, darel->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_directory - output err message cd command in get_cd
 * @darel: data relevant to direcory
 * Return:  show if there is any Error message
 */
char *error_get_directory(list_ti *darel)
{
	int lengthes, length_id;
	char *error, *v_str, *meesg;

	v_str = conv_itst(darel->counter);
	if (darel->args[1][0] == '-')
	{
		meesg = ": Illegal option ";
		length_id = 2;
	}
	else
	{
		meesg = ": can't cd to ";
		length_id = _strlen(darel->args[1]);
	}

	lengthes = _strlen(darel->av[0]) + _strlen(darel->args[0]);
	lengthes += _strlen(v_str) + _strlen(meesg) + length_id + 5;
	error = malloc(sizeof(char) * (lengthes + 1));

	if (error == 0)
	{
		free(v_str);
		return (NULL);
	}

	error = st_con(darel, meesg, error, v_str);

	free(v_str);

	return (error);
}

/**
 * error_not_Messagefound -  display generic error message not found
 * @darel: counter and arguments
 * Return: show if there is any errors message
 */
char *error_not_Messagefound(list_ti *darel)
{
	int lengthes;
	char *error;
	char *v_str;

	v_str = conv_itst(darel->counter);
	lengthes = _strlen(darel->av[0]) + _strlen(v_str);
	lengthes += _strlen(darel->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(v_str);
	return (error);
}

/**
 * error_exit_message - generic error message for exit in get_exit
 * @darel: counter and arguments
 * Return: show if there is any error message
 */
char *error_exit_message(list_ti *darel)
{
	int lengthes;
	char *error;
	char *v_str;

	v_str = conv_itst(darel->counter);
	lengthes = _strlen(darel->av[0]) + _strlen(v_str);
	lengthes += _strlen(darel->args[0]) + _strlen(darel->args[1]) + 23;
	error = malloc(sizeof(char) * (lengthes + 1));
	if (error == 0)
	{
		free(v_str);
		return (NULL);
	}
	_strcpy(error, darel->av[0]);
	_strcat(error, ": ");
	_strcat(error, v_str);
	_strcat(error, ": ");
	_strcat(error, darel->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, darel->args[1]);
	_strcat(error, "\n\0");
	free(v_str);

	return (error);
}


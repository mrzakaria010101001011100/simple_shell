#include "main.h"

/**
 * shell_exit - exits the shell
 * @darel: status and args
 * Return: show 0 if there is success.
 */
int shell_exit(list_ti *darel)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (darel->args[1] != NULL)
	{
		ustatus = _stringint(darel->args[1]);
		is_digit = _isdigitstring(darel->args[1]);
		str_len = _strlen(darel->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			getc_error(darel, 2);
			darel->status = 2;
			return (1);
		}
		darel->status = (ustatus % 256);
	}
	return (0);
}

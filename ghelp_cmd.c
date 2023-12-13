#include "main.h"

/**
 * get_retrivehelp - retrieves help messages builtin
 * @darel: args and input
 * Return: show if the Return value is 0
*/
int get_retrivehelp(list_ti *darel)
{

	if (darel->args[1] == 0)
		help_general();
	else if (_strcmp(darel->args[1], "setenv") == 0)
		help_setenviroment();
	else if (_strcmp(darel->args[1], "env") == 0)
		help_enviroment();
	else if (_strcmp(darel->args[1], "unsetenv") == 0)
		help_unsetenviroment();
	else if (_strcmp(darel->args[1], "help") == 0)
		help_information();
	else if (_strcmp(darel->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(darel->args[1], "cd") == 0)
		help_cd();
	else if (_strcmp(darel->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, darel->args[0],
		      _strlen(darel->args[0]));

	darel->status = 0;
	return (1);
}

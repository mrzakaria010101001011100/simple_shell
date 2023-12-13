#include "main.h"

/**
 * builtin_cmd - builtin command in argument
 * @cmd: command
 * Return: pointer builtin command
 */
int (*builtin_cmd(char *cmd))(list_ti *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", shell_exit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell_dir },
		{ "help", get_retrivehelp },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

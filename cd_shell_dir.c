#include "main.h"

/**
 * cd_shell_dir - changes current directory
 * @darel: data relevant
 * Return: show if it is sucess
 */
int cd_shell_dir(data_shell *darel)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = darel->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_home_dir(darel);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cdirectory_previous(darel);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_parentdot(darel);
		return (1);
	}

	cdirectory_to(darel);

	return (1);
}

#include "main.h"

/**
 * check_cdir - checks current directory.
 * @path: character pointer char.
 * @i: integer pointer of index.
 * Return: 1 if the searchable in the cd otherwise 0
 */
int check_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _whichcmd - locates a command
 * @cmd: command name
 * @_environ: env variable
 * Return: location of the cmd
 */
char *_whichcmd(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _envvariable("PATH", _environ);
	if (path)
	{
		ptr_path = _dupheapmemo(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (check_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_execute - determines if is an executable
 * @darel: data structure
 * Return: return 0 if not executable
 */
int is_execute(list_ti *darel)
{
	struct stat st;
	int i;
	char *input;

	input = darel->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	getc_error(darel, 127);
	return (-1);
}

/**
 * check_error_command - make  user has permissions to access
 * @dir: destination dir
 * @darel: data structure
 * Return: 1 if there is error otherwise 0
 */
int check_error_command(char *dir, list_ti *darel)
{
	if (dir == NULL)
	{
		getc_error(darel, 127);
		return (1);
	}

	if (_strcmp(darel->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			getc_error(darel, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(darel->args[0], X_OK) == -1)
		{
			getc_error(darel, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_execute - executes command lines
 * @darel:  args and input
 * Return: return 1 on success.
 */
int cmd_execute(list_ti *darel)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_execute(darel);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _whichcmd(darel->args[0], darel->_environ);
		if (check_error_command(dir, darel) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _whichcmd(darel->args[0], darel->_environ);
		else
			dir = darel->args[0];
		execve(dir + exec, darel->args, darel->_environ);
	}
	else if (pd < 0)
	{
		perror(darel->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	darel->status = state / 256;
	return (1);
}

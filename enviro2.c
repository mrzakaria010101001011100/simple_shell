#include "main.h"

/**
 * copies_info - copies info
 * to env alias
 * @name: name
 * @value: value
 * Return: new env or alias.
 */
char *copies_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_envi - sets an environment var
 * @name: name of environment var
 * @value: value of  environment var
 * @darel: environ
 * Return show if there is no return
 */
void set_envi(char *name, char *value, list_ti *darel)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; darel->_environ[i]; i++)
	{
		var_env = _dupheapmemo(darel->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(darel->_environ[i]);
			darel->_environ[i] = copies_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	darel->_environ = _redou(darel->_environ, i, sizeof(char *) * (i + 2));
	darel->_environ[i] = copies_info(name, value);
	darel->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @darel: env name and env value
 * Return: display if 1 is success.
 */
int _setenv(list_ti *darel)
{

	if (darel->args[1] == NULL || darel->args[2] == NULL)
	{
		getc_error(darel, -1);
		return (1);
	}

	set_envi(darel->args[1], darel->args[2], darel);

	return (1);
}

/**
 * _unsetenv - deletes environment var
 * @darel: env name
 * Return: display if 1 on success.
 */
int _unsetenv(list_ti *darel)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (darel->args[1] == NULL)
	{
		getc_error(darel, -1);
		return (1);
	}
	k = -1;
	for (i = 0; darel->_environ[i]; i++)
	{
		var_env = _dupheapmemo(darel->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, darel->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		getc_error(darel, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; darel->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = darel->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(darel->_environ[k]);
	free(darel->_environ);
	darel->_environ = realloc_environ;
	return (1);
}

#include "main.h"

/**
 * cd_parentdot - changes to the parent directory
 * @darel: data relevant to the environ
 * Return: show if there is no return
 */
void cd_parentdot(data_shell *darel)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _dupheapmemo(pwd);
	set_envi("OLDPWD", cp_pwd, darel);
	dir = darel->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_envi("PWD", cp_pwd, darel);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	reverse_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			reverse_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_envi("PWD", cp_strtok_pwd, darel);
	}
	else
	{
		chdir("/");
		set_envi("PWD", "/", darel);
	}
	darel->status = 0;
	free(cp_pwd);
}

/**
 * cdirectory_to - changes to a directory given
 * by user
 * @darel: data relevant of the dir
 * Return: show if there is no return
 */
void cdirectory_to(data_shell *darel)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = darel->args[1];
	if (chdir(dir) == -1)
	{
		getc_error(darel, 2);
		return;
	}

	cp_pwd = _dupheapmemo(pwd);
	set_envi("OLDPWD", cp_pwd, darel);

	cp_dir = _dupheapmemo(dir);
	set_envi("PWD", cp_dir, darel);

	free(cp_pwd);
	free(cp_dir);

	darel->status = 0;

	chdir(dir);
}

/**
 * cdirectory_previous - changes to the previous directory
 * @darel: environ
 * Return: show if there is no return
 */
void cdirectory_previous(data_shell *darel)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _dupheapmemo(pwd);

	p_oldpwd = _envvariable("OLDPWD", darel->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _dupheapmemo(p_oldpwd);

	set_envi("OLDPWD", cp_pwd, darel);

	if (chdir(cp_oldpwd) == -1)
		set_envi("PWD", cp_pwd, darel);
	else
		set_envi("PWD", cp_oldpwd, darel);

	p_pwd = _envvariable("PWD", darel->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	darel->status = 0;

	chdir(p_pwd);
}

/**
 * cd_home_dir - changes to home directory
 * @darel: environ
 * Return: show if there is no return
 */
void cd_home_dir(list_ti *darel)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _dupheapmemo(pwd);

	home = _envvariable("HOME", darel->_environ);

	if (home == NULL)
	{
		set_envi("OLDPWD", p_pwd, darel);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		getc_error(darel, 2);
		free(p_pwd);
		return;
	}

	set_envi("OLDPWD", p_pwd, darel);
	set_envi("PWD", home, darel);
	free(p_pwd);
	darel->status = 0;
}

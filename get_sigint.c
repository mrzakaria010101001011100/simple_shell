#include "main.h"

/**
 * get_prompt - Handle the crtl + c prompt
 * @sig: Signal handler
 */
void get_prompt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

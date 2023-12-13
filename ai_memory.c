#include "main.h"

/**
 * _copyinfo - copies the info in the void pointers.
 * @newptr: last pointer.
 * @ptr: main pointer.
 * @size: show size new pointer.
 * Return: show if there is no return.
 */
void _copyinfo(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _reallocmemo - reallocation  memory block.
 * @ptr: pointer memory previously allocated.
 * @old_size: size of the allocated space ptr.
 * @new_size: new size of the new memory block.
 * Return: ptr.
 * new_size == old_size, returns ptr.
 * malloc fails, returns NULL.
 */
void *_reallocmemo(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_copyinfo(newptr, ptr, new_size);
	else
		_copyinfo(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _redou - reallocates a memory block of double pointer.
 * @ptr: double pointer memory previously allocated.
 * @old_size: size of the allocated space ptr.
 * @new_size: new size of new memory block.
 * Return: ptr.
 * new_size == old_size, returns ptr without changes.
 * malloc fails, returns NULL.
 */
char **_redou(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}

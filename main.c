#include "shell.h"

/**
 * main - the main function
 * @countarr: Numbers of arguments
 * @arr: array of arguments
 * Return: zero or one
 */
int main(int countarr, char **arr)
{
	int descF = 2;
	type_info f[] = {InitInfo};

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(descF)
		: "r"(descF));
	if (countarr == 2)
	{
		descF = open(arr[1], O_RDONLY);
		if (descF == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				our_Eputs(arr[0]);
				our_Eputs(": 0: Can't open ");
				our_Eputs(arr[1]);
				our_Eputchar('\n');
				our_Eputchar(BufFlush);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		f->readfd = descF;
	}
	Env_list_Pop(f);
	Hist_reading(f);
	mHSH(f, arr);
	return (EXIT_SUCCESS);
}

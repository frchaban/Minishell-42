#include "includes/minishell.h"

int main (void)
{
	int fd1;
	int fd2;

	fd1 = open("test.txt", O_WRONLY);
	fd2 = open("test2.txt", O_WRONLY);
	dup2(fd1, 1);
	dup2(fd2, 1);
	printf("1111111");

}
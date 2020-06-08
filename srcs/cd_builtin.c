#include "minishell.h"


void	cd_builtin(char **cmd)
{
	(void)cmd;
}

void	cd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_printf("%s\n", strerror(errno));
	}
}

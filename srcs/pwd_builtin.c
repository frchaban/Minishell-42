#include "minishell.h"

void	pwd_builtin(void)
{
	char *buf;
	buf = NULL;

	if (getcwd(buf, 0) != NULL)
	{
		ft_printf("%s\n", buf);
	}
	else
	{
		ft_printf("%s\n", strerror(errno));
	}
}

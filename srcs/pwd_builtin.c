#include "minishell.h"

void	pwd_builtin(char **cmd)
{
	char *buf;
	buf = NULL;

	if (ft_count_split(cmd) > 1)
		return (ft_error("pwd: too many arguments", NULL, NULL));
	if (getcwd(buf, 0) != NULL)
	{
		ft_printf("%s\n", getcwd(buf, 0));
	}
	else
	{
		ft_printf("%s\n", strerror(errno));
	}
}

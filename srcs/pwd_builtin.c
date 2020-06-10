#include "minishell.h"

void	pwd_builtin(t_list *args)
{
	char *buf;
	buf = NULL;

	if (args_size(args) > 0)
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

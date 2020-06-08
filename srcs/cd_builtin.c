#include "minishell.h"

void	update_pwd(char *pwd, char *old_pwd, t_env *envir)
{
	t_env *lst;

	lst = envir;
	while (envir)
	{
		if (ft_strequ(envir->key, "PWD") == 1)
		{
			free(envir->content);
			envir->content = pwd;
		}
		else if (ft_strequ(envir->key, "OLDPWD") == 1)
		{
			free(envir->content);
			envir->content = old_pwd;
		}
		envir = envir->next;
	}
	envir = lst;
}

int		cd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		return (0);
	}
	return (1);
}

char	*get_home(t_env *envir)
{
	t_env *lst;

	lst = envir;
	while (lst)
	{
		if (ft_strequ(lst->key, "HOME") == 1)
			return (lst->content);
		else
			lst = lst->next;
	}
	return (NULL);
}

void	cd_builtin(char **cmd, t_env *envir)
{
	char *pwd;
	char *old_pwd;
	int res;

	old_pwd = getcwd(NULL,0);
	res = (cmd[1] == NULL ? cd(get_home(envir)) : cd(cmd[1]));
	if (res == 1)
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		printf("%s\n", old_pwd);
		update_pwd(pwd,old_pwd,envir);
	}
}

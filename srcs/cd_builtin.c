#include "minishell.h"

void	update_pwd(char *pwd, char *old_pwd, t_env *envir)
{
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
}

int		cd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_error("cd: ", strerror(errno), path);
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

void	cd_builtin(t_list *args, t_env *envir)
{
	char *pwd;
	char *old_pwd;
	int res;

	if (args_size(args) > 2)
		return (ft_error("cd: too many arguments", NULL, NULL));
	else if (args_size(args) == 2)
		return (ft_error("cd: string not in pwd: ", NULL, args->next->content));
	old_pwd = getcwd(NULL,0);
	res = (args == NULL ? cd(get_home(envir)) : cd(args->content));
	if (res == 1)
	{
		pwd = getcwd(NULL, 0);
		update_pwd(pwd,old_pwd,envir);
		return;
	}
	free(old_pwd);
}

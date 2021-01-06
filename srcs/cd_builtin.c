/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:59:40 by user42            #+#    #+#             */
/*   Updated: 2021/01/05 16:34:59 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int		cd(char *path, t_env *env)
{
	if (chdir(path) == -1)
	{
		ft_error("cd: no such file or directory: ", path, 1, env);
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
	char	*pwd;
	char	*old_pwd;
	int		res;

	if (args_size(args) > 2)
		return (ft_error("cd: too many arguments", NULL, 1, envir));
	else if (args_size(args) == 2)
		return (ft_error("cd: string not in pwd: ", args->content, 1, envir));
	old_pwd = getcwd(NULL, 0);
	res = (args == NULL ? cd(get_home(envir), envir) :
	cd(args->content, envir));
	if (res == 1)
	{
		pwd = getcwd(NULL, 0);
		update_pwd(pwd, old_pwd, envir);
		free(old_pwd);
		free(pwd);
		return ;
	}
	free(old_pwd);
}

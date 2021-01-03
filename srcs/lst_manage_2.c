/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manage_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:59:57 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/16 17:00:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		args_size(t_list *args)
{
	int i;

	i = 0;
	while (args != NULL)
	{
		i++;
		args = args->next;
	}
	return (i);
}

int		lst_size(t_env *env)
{
	int i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**list_to_envp(t_env *env)
{
	char	**final;
	int		i;
	int		len;
	int		size;

	size = lst_size(env);
	if (!(final = malloc(sizeof(*final) * (size + 1))))
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->exportable == EXPORT)
		{
			len = ft_strlen(env->key) + ft_strlen(env->content) + 1;
			if (!(final[i] = malloc(sizeof(**final) * (len + 1))))
				return (NULL);
			final[i][0] = '\0';
			ft_strcat(final[i], env->key);
			ft_strcat(final[i], "=");
			ft_strcat(final[i++], env->content);
		}
		env = env->next;
	}
	final[i] = NULL;
	return (final);
}

char	*get_var_content(char *cmd, t_env *envir)
{
	char *tronc;

	tronc = ft_substr(cmd, 0, ft_strlen(cmd));
	free(cmd);
	while (envir)
	{
		if (ft_strequ(tronc, envir->key) == 1)
		{
			free(tronc);
			return (ft_strdup(envir->content));
		}
		envir = envir->next;
	}
	if (tronc && ft_strequ(tronc, "$"))
		return (tronc);
	free(tronc);
	return (ft_strdup(""));
}

int		check_valid_var(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '=')
			return (0);
		if (ft_strchr(cmd[i], '=') == 0)
			return (0);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:46:51 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/10 16:06:10 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_find_key(t_env *envir, char *cmd)
{
	while (envir)
	{
		if (ft_strcmp(cmd, envir->key) == 0)
			return (1);
		envir = envir->next;
	}
	return (0);
}

void	export_print_lst(t_env *envir)
{
	char	**temp;
	t_env	*ordered;

	temp = list_to_envp(envir);
	ft_sort_strings(temp);
	envp_to_list(&ordered, temp);
	while (ordered)
	{
		if (ordered->exportable == 1)
			ft_printf("declare -x %s=\"%s\"\n", ordered->key, ordered->content);
		ordered = ordered->next;
	}
	free(temp);
	free_all_list(ordered);
}

int		check_valid_cmd(char *cmd)
{
	char	c;
	int		i;

	i = 0;
	while (cmd[i])
	{
		c = cmd[i];
		if ((c > 'z' || c < '0' || (c > '9' && c < 'A') || ( c > 'Z' && c < 'a')) && c != '=')
		{
			ft_error("issue with your command : ", "export", cmd);
			return (0);
		}
		i++;
	}
	return (1);
}

void	export_elem_to_envir(t_env *envir, char *cmd)
{
	t_env	*next;
	t_env	*previous;
	char	*equal;

	equal = ft_strchr(cmd, '=');
	next = set_up_elem(cmd, EXPORT);
	while (envir)
	{
		previous = envir;
		if (ft_strcmp(envir->key, next->key) == 0)
		{
			if (equal)
			{
				free(envir->content);
				envir->content = next->content;
			}
			envir->exportable = EXPORT;
			free(next->key);
			free(next);
			return ;
		}
		envir = envir->next;
	}
	previous->next = next;
}

void	export_builtin(t_env *envir, t_list *args)
{
	t_list	*begin;

	if (!args)
		export_print_lst(envir);
	else
	{
		begin = args;
		while (args)
		{
			if (check_valid_cmd(args->content) == 0)
				return ;
			args = args->next;
		}
		args = begin;
		while (args)
		{
			export_elem_to_envir(envir, args->content);
			args = args->next;
		}
	}
}

/*
** 
*/

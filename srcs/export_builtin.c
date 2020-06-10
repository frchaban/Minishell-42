/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:46:51 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/10 10:21:49 by gdupont          ###   ########.fr       */
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

void	export_print_lst()
{
	;
}

int		check_valid_cmd(char *cmd)
{
	if (cmd == ft_strchr(cmd, '='))
	{
		ft_error(cmd, NULL, "export");
		return (0);
	}
	return (1);
}

void	export_elem_to_envir(t_env *envir, char *cmd)
{
	t_env	*next;
	t_env	*previous;

	next = set_up_elem(cmd, 1);
	while (envir)
	{
		previous = envir;
		if (ft_strcmp(envir->key, next->key) == 0)
		{
			free(envir->content);
			envir->content = next->content;
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
		export_print_lst();
	else
	{
		begin = args;
		while (args)
		{
			if (check_valid_cmd(args->content) == 0)
				return ;
		}
		args = begin;
		while (args)
		{
			export_elem_to_envir(envir, args->content);
			args = args->next;
		}
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:30:54 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/10 22:51:02 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_valid_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '=') && cmd[0] != '=')
	{
		return (1);
	}
	return (0);
}

void		add_variable_to_envir(t_env *envir, char *cmd)
{
	t_env	*next;
	t_env	*previous;

	next = set_up_elem(cmd, NOT_EXPORT);
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

void	variable_update(char *first_cmd, t_list *args, t_env *envir)
{
	t_list	*begin;

	begin = args;
	if (check_valid_cmd(first_cmd) == 0)
		return ;
	while (args)
	{
		if (check_valid_cmd(args->content) == 0)
			return ;
		args = args->next;
	}
	add_variable_to_envir(envir, first_cmd);
	while (begin)
	{
		add_variable_to_envir(envir, begin->content);
		begin = begin->next;
	}
}

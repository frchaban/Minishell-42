/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 22:06:03 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/10 23:25:50 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_valid_cmd(char *cmd)
{
	(void)cmd;
	return (1);
}

void		remove_variable_from_envir(t_env *envir, char *cmd)
{
	while (envir)
	{
		if (ft_strcmp(envir->key, cmd) == 0 && envir->exportable == 0)
		{
			free(envir->content);
			envir->content = ft_strdup("");
			return ;
		}
		else
		envir = envir->next;
	}
}

void	unset_builtin(t_list *args, t_env *envir)
{
	t_list	*begin;

	begin = args;
	while (args)
	{
		if (check_valid_cmd(args->content) == 0)
			return ;
		args = args->next;
	}
	while (begin)
	{
		remove_variable_from_envir(envir, begin->content);
		begin = begin->next;
	}
}

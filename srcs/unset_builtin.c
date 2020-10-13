/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 22:06:03 by gdupont           #+#    #+#             */
/*   Updated: 2020/10/13 12:35:27 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	check_valid_cmd(char *cmd)
{
	int		i;
	t_env	*temp;
	int		result;

	i = 0;
	result = 1;
	temp = set_up_elem(cmd, EXPORT);
	if (ft_isdigit(temp->key[0]))
		result = 0;
	while (temp->key[i])
	{
		if (!ft_isalnum(temp->key[i]) && temp->key[i] != '_')
			result = 0;
		i++;
	}
	free_elem_list(temp);
	return (result);
}

void		remove_variable_from_envir(t_env *envir, char *cmd)
{
	t_env	*previous;

	while (envir)
	{
		if (ft_strcmp(envir->key, cmd) == 0)
		{
			previous->next = envir->next;
			free_elem_list(envir);
			return ;
		}
		previous = envir;
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
		{
			ft_error("minishell: no matches found: ", args->content, 1, envir); //done
			return ;
		}
		args = args->next;
	}
	while (begin)
	{
		remove_variable_from_envir(envir, begin->content);
		begin = begin->next;
	}
}

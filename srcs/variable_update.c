/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:30:54 by gdupont           #+#    #+#             */
/*   Updated: 2020/12/14 19:10:04 by user42           ###   ########.fr       */
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

void		variable_update(char *first_cmd, t_list *args, t_env *envir)
{
	t_list	*begin;
	int		result;

	begin = args;
	result = 1;
	if (check_valid_cmd(first_cmd) == 0)
		result = 0;
	while (args)
	{
		if (check_valid_cmd(args->content) == 0)
			result = 0;
		args = args->next;
	}
	if (!result)
		return (ft_error("minishell: no matches found: ", first_cmd, 1, NULL));
	add_variable_to_envir(envir, first_cmd);
	while (begin)
	{
		add_variable_to_envir(envir, begin->content);
		begin = begin->next;
	}
}

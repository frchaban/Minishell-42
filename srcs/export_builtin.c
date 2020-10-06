/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:46:51 by gdupont           #+#    #+#             */
/*   Updated: 2020/10/06 11:41:06 by gdupont          ###   ########.fr       */
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

void		export_print_lst(t_env *envir)
{
	char	**temp;
	t_env	*ordered;

	temp = list_to_envp(envir);
	ft_sort_strings(temp);
	envp_to_list(&ordered, temp);
	while (ordered)
	{
		if (ordered->exportable == 1)
			ft_printf("%s=\'%s\'\n", ordered->key, ordered->content);
		ordered = ordered->next;
	}
	free(temp);
	free_all_list(ordered);
}

void		export_elem_to_envir(t_env *envir, char *cmd)
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
			envir->exportable = EXPORT;
			if (equal)
			{
				envir->content = next->content;
				free(next->key);
				free(next);
				return ;
			}
		}
		envir = envir->next;
	}
	if (equal)
		previous->next = next;
	else
		free_elem_list(next);
}

void		export_builtin(t_env *envir, t_list *args)
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
			{
				ft_error("issue with this command: ", NULL, args->content);
				return ;
			}
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


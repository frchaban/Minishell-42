/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:46:51 by gdupont           #+#    #+#             */
/*   Updated: 2020/12/15 16:18:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*check_valid_cmd(char *cmd)
{
	int		i;
	t_env	*temp;
	char	*result;

	i = 0;
	result = NULL;
	temp = set_up_elem(cmd, EXPORT);
	if (ft_isdigit(temp->key[0]) || cmd[0] == '=')
		result = "export: not an identifier: ";
	while (temp->key[i])
	{
		if (!ft_isalnum(temp->key[i]) && temp->key[i] != '_')
			result = "minishell: no matches found: ";
		i++;
	}
	free_elem_list(temp);
	return (result);
}

void			export_print_lst(t_env *envir)
{
	char	**temp;
	t_env	*ordered;
	t_env	*ordered_for_free;

	temp = list_to_envp(envir);
	ft_sort_strings(temp);
	envp_to_list(&ordered, temp);
	ordered_for_free = ordered;
	while (ordered)
	{
		if (ordered->exportable == 1)
		{
			ft_printf("declare -x %s", ordered->key);
			if (ordered->content && ordered->content[0])
				ft_printf("=\"%s\"", ordered->content);
			ft_putchar('\n');
		}
		ordered = ordered->next;
	}
	ft_free_2dim(temp);
	free_all_list(ordered_for_free);
}

void			export_elem_to_envir(t_env *envir, char *cmd)
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
	previous->next = next;
}

void			export_builtin(t_env *envir, t_list *args)
{
	t_list	*begin;
	char	*error_msg;

	if (!args)
		export_print_lst(envir);
	else
	{
		begin = args;
		while (args)
		{
			if ((error_msg = check_valid_cmd(args->content)) != NULL)
			{
				errno = 1;
				ft_error(error_msg, args->content, 1, envir);
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

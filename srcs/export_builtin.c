/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:46:51 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/09 17:58:19 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_find_key(t_env *envir, char *cmd)
{
	while (envir)
	{
		if (ft_strcmp(cmd, envir->key) == 0)
			return (1);
		envir = envir->key;
	}
	return (0);
}

void	export_print_lst()
{
	;
}

int		check_valid_cmd(t_env *envir, char *cmd)
{
	int		y;
	char	*key;

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


void	export_builtin(t_env *envir, char **cmd)
{
	int i;

	if (cmd[1] != NULL)
		export_print_lst();
	else if (cmd[1][0] = '\0')
		export_print_lst();
	else
	{
		i = 1;
		while (cmd[i])
		{
			if (check_valid_cmd(envir, cmd[i++]) == 0)
				return ;
		}
		i = 1;
		while (cmd[i])
			export_elem_to_envir(envir, cmd[i++])
	}
}

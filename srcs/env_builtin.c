/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:02:36 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/09 09:28:27 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_common_key(char *key, t_env *temp, char **to_print)
{
	if (!temp)
		return (0);
	while (temp)
	{
		*to_print = temp->content;
		if (ft_strcmp(key, temp->key) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	print_envir_and_temp(t_env *envir, t_env *temp)
{
	char *to_print;

	to_print = NULL;
	while (envir)
	{
		ft_printf("%s=", envir->key);
		if (is_common_key(envir->key, temp, &to_print) == 1)
			ft_putendl(to_print);
		else
			ft_putendl(envir->content);
		envir = envir->next;
	}
}

void	env_builtin(t_env *envir, char **cmd)
{
	t_env	*temp;
	char	*to_print;

	temp = NULL;
	if (cmd[1] != NULL)
	{
		if (envp_to_list(&temp, &cmd[1]) == -1)
			return ;
	}
	print_envir_and_temp(envir, temp);
	to_print = NULL;
	while (temp)
	{
		if (is_common_key(temp->key, envir, &to_print) == 0)
			ft_printf("%s=%s\n", temp->key, temp->content);
		temp = temp->next;
	}
	free_all_list(temp);
}

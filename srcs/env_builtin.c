/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:02:36 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/10 11:31:59 by gdupont          ###   ########.fr       */
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

void	env_builtin(t_env *envir)
{
	while (envir)
	{
		if (envir->exportable == 1)
			printf("%s=%s\n", envir->key, envir->content);
		envir = envir->next;
	}
}

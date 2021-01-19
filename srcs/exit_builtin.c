/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:00:33 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 11:45:34 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		exit_builtin(t_list *args, t_env *env)
{
	if (args && args->next)
	{
		ft_error("exit\n", "minishell: exit: too many arguments", 131, env);
		return (1);
	}
	else if (args && !ft_s_isdigit((char *)args->content)
		&& ((char *)args->content)[0] != '-'
		&& ((char *)args->content)[0] != '+')
	{
		ft_error("exit\n", "minishell: exit: argument numerique necessaire",
		2, env);
		return (0);
	}
	else if (args)
		errno = ft_atoi(args->content);
	else
		errno = 0;
	if (errno < 0)
		errno += 256;
	errno %= 256;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:31:31 by user42            #+#    #+#             */
/*   Updated: 2021/01/11 15:35:14 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *cmd_n_error_msg, char *arg, int error_nb, t_env *env)
{
	ft_putstr("salut\n");
	if (env)
	{
		free(env->content);
		env->content = ft_itoa(error_nb);
	}
	if (cmd_n_error_msg)
		ft_putstr_fd(cmd_n_error_msg, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	errno = error_nb;
}

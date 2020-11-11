/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:00:47 by user42            #+#    #+#             */
/*   Updated: 2020/11/11 13:00:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_builtin(t_list *args, t_env *env)
{
	char *buf;

	buf = NULL;
	if (args_size(args) > 0)
		return (ft_error("pwd: too many arguments", NULL, 1, env));
	if (getcwd(buf, 0) != NULL)
		ft_printf("%s\n", getcwd(buf, 0));
	else
		ft_printf("%s\n", strerror(errno));
}

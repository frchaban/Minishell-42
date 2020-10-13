/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:02:36 by gdupont           #+#    #+#             */
/*   Updated: 2020/10/13 11:14:17 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_builtin(t_env *envir)
{
	while (envir)
	{
		if (envir->exportable == 1)
			ft_printf("%s=%s\n", envir->key, envir->content);
		envir = envir->next;
	}
}

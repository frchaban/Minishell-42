/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:51:55 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/08 16:33:15 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *content)
{
	if (content == NULL)
		ft_printf("%s", "");
	else
		ft_printf("%s", content);
}

void	echo_builtin(char **cmd)
{
	int i;
	int option;

	if (ft_strequ(cmd[1], "-n") == 1)
	{
		i = 1;
		option =1;
	}
	else
	{
		i = 0;
		option = 0;
	}
	while (cmd[++i])
	{
		echo(cmd[i]);
	}
	option == 0 ? ft_printf("\n") : 0;
	return;
}

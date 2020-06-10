/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:51:55 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/10 11:08:59 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_list *args)
{
	int		flag;
	int		mult;

	flag = 0;
	mult = 0;
	if (args)
	{
		flag = ((ft_strequ(args->content, "-n") ? 0 : 1));
		if (flag == 1)
			mult = ((args_size(args) > 1) ? 1 : 0);
		else
			mult = ((args_size(args) > 2) ? 1 : 0);
	}
	if (flag == 0)
		args = args->next;
	while(args)
	{
		ft_printf("%s", args->content);
		if (mult == 1 && args->next)
			ft_printf(" ");
		args = args->next;
	}
	flag == 1 ? ft_printf("\n") : 0;
}

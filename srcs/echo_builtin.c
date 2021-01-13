/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:51:55 by frchaban          #+#    #+#             */
/*   Updated: 2021/01/13 15:39:27 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_write(char *line)
{
	int i;

	i = -1;
	if (ft_strequ(line, "-n"))
		return (0);
	else
		ft_putstr(line);
	return (1);
}

void		echo_builtin(t_list *args)
{
	int		newline;
	int		mult;

	newline = 0;
	mult = 0;
	!args ? ft_printf("\n") : 0;
	if (args)
	{
		newline = ((ft_strequ(args->content, "-n") ? 0 : 1));
		if (newline == 1)
			mult = ((args_size(args) > 1) ? 1 : 0);
		else
			mult = ((args_size(args) > 2) ? 1 : 0);
	}
	if (args && newline == 0)
		args = args->next;
	while (args)
	{
		if (ft_write(args->content) && mult == 1 && args->next)
			ft_printf(" ");
		args = args->next;
	}
	newline == 1 ? ft_printf("\n") : 0;
	errno = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:51:55 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/15 12:01:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_write(char *line)
{
	int i;

	i = -1;
	if (ft_strequ(line, "-n"))
		return (0);
	while (line[++i])
	{
		if (line[i] == '\\')
			write(1, &line[i], 0);
		else if (i != 0 && line[i - 1] != '\\'
		&& (line[i] == '\"' || line[i] == '\''))
			write(1, &line[i], 0);
		else
			write(1, &line[i], 1);
	}
	return (1);
}


void		echo_builtin(t_list *args)
{
	int		flag;
	int		mult;

	flag = 0;
	mult = 0;
	!args ? ft_printf("\n") : 0;
	if (args)
	{
		flag = ((ft_strequ(args->content, "-n") ? 0 : 1));
		if (flag == 1)
			mult = ((args_size(args) > 1) ? 1 : 0);
		else
			mult = ((args_size(args) > 2) ? 1 : 0);
	}
	if (args && flag == 0)
		args = args->next;
	while (args)
	{
		if (ft_write(args->content) && mult == 1 && args->next)
			ft_printf(" ");
		args = args->next;
	}
	flag == 1 ? ft_printf("\n") : 0;
	errno = 0;
}

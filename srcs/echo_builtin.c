/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:51:55 by frchaban          #+#    #+#             */
/*   Updated: 2020/05/25 14:59:21 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *content, int option)
{
	if (option == 0)
	{
		if (content == NULL)
			ft_printf("%s\n", "");
		else
			ft_printf("%s\n", content);
	}
	else
	{
		if (content == NULL)
			ft_printf("%s", "");
		else
			ft_printf("%s", content);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:50:31 by gdupont           #+#    #+#             */
/*   Updated: 2020/07/29 15:53:39 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_print_split_fd(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		ft_putchar_fd('-', 2);
		ft_putstr_fd(split[i], 2);
		ft_putstr_fd("-\n", 2);
		i++;
	}
}

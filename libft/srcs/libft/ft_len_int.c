/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:03:44 by frchaban          #+#    #+#             */
/*   Updated: 2020/04/27 17:17:50 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_int(int n)
{
	int size;

	if (n < 0)
	{
		n = n * -1;
		size = 1;
	}
	else
		size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 20:53:38 by frchaban          #+#    #+#             */
/*   Updated: 2020/05/25 11:43:13 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

float	ft_atof(const char *str)
{
	int		atoi;
	float	atof;
	int		fac;
	int		i;

	i = 0;
	atof = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	atoi = ft_atoi(str);
	fac = (atoi < 0 || (atoi == 0 && str[i] == '-') ? -1 : 1);
	i += ((atoi == 0 && str[i] == '-') ? 1 : 0);
	i += ft_len_int(atoi);
	if (str[i++] != '.')
		return (atoi);
	while (str[i] && ft_isdigit(str[i]))
	{
		fac *= 10;
		atof = atof * 10 + (str[i++] - 48);
	}
	return (atoi + atof / fac);
}

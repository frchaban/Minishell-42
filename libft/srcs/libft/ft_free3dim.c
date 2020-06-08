/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free3dim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:30:55 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/08 13:33:34 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_3dim(char ***data)
{
	int i;
	int j;
	j = -1;
	while (data[++j])
	{
		i = -1;
		while (data[j][++i])
			free(data[j][i]);
		free(data[j]);
	}
	free(data);
}

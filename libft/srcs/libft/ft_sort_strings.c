/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:20:07 by gdupont           #+#    #+#             */
/*   Updated: 2020/12/09 12:51:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_sort_strings(char **strings)
{
	int		i;
	char	*temp;

	i = 0;
	if (!strings)
		return ;
	if (!strings[1])
		return ;
	while (strings[i + 1])
	{
		if (ft_strcmp(strings[i], strings[i + 1]) > 0)
		{
			temp = strings[i];
			strings[i] = strings[i + 1];
			strings[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

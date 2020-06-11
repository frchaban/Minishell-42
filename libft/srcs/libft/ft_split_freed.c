/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_freed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:42:27 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/11 14:45:59 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(char *s, unsigned int pos, char c)
{
	unsigned int	i;

	i = 0;
	while (s[pos + i] && s[pos + i] != c)
		i++;
	return (i);
}

static size_t	ft_len(char *s, char c)
{
	unsigned int	cpt;
	unsigned int	i;
	size_t			len;

	cpt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = ft_wordlen(s, i, c);
			cpt++;
			i = i + len;
		}
		else
			i++;
	}
	return (cpt);
}

char			**ft_split_freed(char *s, char c)
{
	unsigned int	cpt;
	char			**split;
	unsigned int	i;
	size_t			len;

	if (s == NULL)
		return (NULL);
	if (!(split = (char **)malloc(sizeof(*split) * (ft_len(s, c) + 1))))
		return (NULL);
	cpt = 0;
	i = 0;
	while (s[i])
		if (s[i] != c)
		{
			len = ft_wordlen(s, i, c);
			split[cpt] = ft_substr(s, i, len);
			cpt++;
			i = i + len;
		}
		else
			i++;
	split[cpt] = 0;
	free(s);
	return (split);
}

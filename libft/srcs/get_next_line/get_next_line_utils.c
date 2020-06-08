/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:36:48 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/08 15:37:10 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strl(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr_mod(char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strl(s);
	if (start >= s_len)
		len = 0;
	else
		len = (s_len - start < len ? s_len - start : len);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	i = 0;
	while (len > 0 && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	free(s);
	return (str);
}

int		ft_strchr_mod(const char *s, char c)
{
	unsigned int i;

	i = 0;
	if (!s)
		return (0);
	while (i < ft_strl(s) + 1)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_mod(char *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*s;

	if (!s1 || !s2)
		return (NULL);
	if (!(s = (char *)malloc(sizeof(*s) * (ft_strl(s1) + ft_strl(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	free(s1);
	return (s);
}

char	*ft_strdup_mod(const char *src)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(sizeof(*src) * (ft_strl(src) + 1));
	if (ptr == NULL)
		return (0);
	while (i < (int)ft_strl(src))
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

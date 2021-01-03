/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:34:40 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/21 17:53:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_set_line(char const *str, char *line)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!str)
		return (ft_strdup_mod(""));
	while (str[i] && str[i] != '\n')
		i++;
	if (!(line = (char *)malloc(sizeof(*line) * (i + 1))))
		return (NULL);
	line[i] = '\0';
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	return (line);
}

char	*ft_read(int fd, char *str, int *flag)
{
	int		rd;
	char	buffer[BUFFER_SIZE + 1];

	while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rd] = '\0';
		if (str && str[0] != '\0')
			str = ft_strjoin_mod(str, buffer);
		else
			str = ft_strjoin_mod(ft_strdup_mod(""), buffer);
		if (ft_strchr_mod(buffer, '\n'))
			return (str);
	}
	if (rd == 0)
		*flag = 1;
	else if (rd == -1)
		return (NULL);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	int			flag;

	flag = 0;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!(str && ft_strchr_mod(str, '\n')))
	{
		str = ft_read(fd, str, &flag);
		if (str == NULL && fd != 0 && flag == 0)
			return (-1);
	}
	*line = ft_set_line(str, *line);
	str = ft_substr_mod(str, ft_strl(*line) + 1, ft_strl(str));
	if (str && str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
	if (flag == 0)
		return (1);
	return (0);
}

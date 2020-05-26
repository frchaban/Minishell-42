/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:34:55 by frchaban          #+#    #+#             */
/*   Updated: 2020/05/25 12:14:55 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define BUFFER_SIZE 40

size_t	ft_strl(const char *s);
char	*ft_substr_mod(char *s, unsigned int start, size_t len);
char	*ft_strdup_mod(const char *src);
char	*ft_strjoin_mod(char *s1, char const *s2);
char	*ft_set_line(char const *str, char *line);
int		get_next_line(int fd, char **line);
int		ft_strchr_mod(const char *s, char c);

#endif

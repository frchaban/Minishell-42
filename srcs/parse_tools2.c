/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:33:23 by gdupont           #+#    #+#             */
/*   Updated: 2021/01/08 16:40:01 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_hashtag(char *line)
{
	int i;
	int simple_q;
	int double_q;

	i = -1;
	simple_q = 0;
	double_q = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && !is_escaped(line, i - 1))
			simple_q++;
		else if (line[i] == '\"' && !is_escaped(line, i - 1))
			double_q++;
		else if (!i && line[i] == '#')
		{
			line[i] = '\0';
			line[i + 1] = '\0';
		}
		else if (line[i] == '#' && !is_escaped(line, i - 1) &&
		ft_strchr(" \t", line[i - 1]) && !(simple_q % 2) && !(double_q % 2))
		{
			line[i] = '\0';
			line[i + 1] = '\0';
		}
	}
}

void	check_double_semicolon(char *line, t_env *envir)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';' && !is_escaped(line, i - 1) && line[i + 1] == ';')
		{
			ft_error("syntax error near unexpected token `;;'",
				NULL, 258, envir);
			line[0] = '\0';
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:33:23 by gdupont           #+#    #+#             */
/*   Updated: 2021/01/19 15:19:22 by gdupont          ###   ########.fr       */
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
	int quote[2];

	i = -1;
	quote[0] = 0;
	quote[1] = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && !is_escaped(line, i - 1))
			quote[0] += 1;
		if (line[i] == '\"' && !is_escaped(line, i - 1))
			quote[1] += 1;
		if (line[i] == ';' && !is_escaped(line, i - 1) && line[i + 1] == ';'
		&& !(quote[0] % 2) && !(quote[1] % 2))
		{
			ft_error("syntax error near unexpected token `;;'",
				NULL, 258, envir);
			line[0] = '\0';
		}
	}
	if (line[0] == ';' || line[0] == '|')
	{
		ft_error("syntax error near unexpected token ", &line[0], 258, envir);
		line[0] = '\0';
	}
}

int		pass_whitespaces(char *line, int i)
{
	while (line[i] && ft_strchr(" \t", line[i]))
		i++;
	return (i);
}

char	**put_back_character(char *line, char c)
{
	char	**final;
	int		i;
	int		j;

	final = ft_split(line, c);
	if (!final)
		return (NULL);
	i = -1;
	while (final[++i])
	{
		j = -1;
		while (final[i][++j])
			final[i][j] == 7 ? final[i][j] = c : 0;
	}
	return (final);
}

char	**handle_inside_quote_split(char *line, char c)
{
	int		i;
	int		simple;
	int		double_q;

	i = -1;
	simple = 0;
	double_q = 0;
	while (line[++i])
	{
		line[i] == '\'' && !is_escaped(line, i - 1) && !(double_q % 2)
		? simple++ : 0;
		line[i] == '\"' && !is_escaped(line, i - 1) && !(simple % 2)
		? double_q++ : 0;
		if (line[i] == c && (simple % 2 || double_q % 2 ||
		is_escaped(line, i - 1)))
			line[i] = 7;
	}
	return (put_back_character(line, c));
}

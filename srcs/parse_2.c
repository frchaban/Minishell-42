/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:02:45 by user42            #+#    #+#             */
/*   Updated: 2021/01/11 09:15:17 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_valid_quote_nb(char *cmd)
{
	int	nb_simple_quote;
	int	nb_double_quote;
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	nb_simple_quote = 0;
	nb_double_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && !is_escaped(cmd, i - 1))
			nb_simple_quote++;
		if (cmd[i] == '\"' && !is_escaped(cmd, i - 1))
			nb_double_quote++;
		i++;
	}
	if (nb_simple_quote % 2 != 0 || (nb_double_quote % 2 != 0))
		return (0);
	return (1);
}

char	*update_line(char *line, int i, t_env *envir)
{
	char	*final;
	int		len_final;
	int		y;
	char	*tronc;

	y = 1;
	while (line[i + y] && line[i + y] != '$' && line[i + y] != ' '
		&& line[i + y] != '=' && line[i + y] != '\"' &&
		line[i + y] != '\'' && line[i + y] != '?' &&
		!ft_isdigit(line[i + y]) && line[i + y] != '\\')
		y++;
	tronc = ft_substr(line, i + 1, y - 1);
	tronc = get_var_content(tronc, envir);
	len_final = ft_strlen(line) - y + 1 + ft_strlen(tronc);
	if (!(final = malloc(sizeof(*final) * len_final + 1)))
		return (NULL);
	final[0] = '\0';
	ft_strncat(final, line, i);
	ft_strcat(final, tronc);
	free(tronc);
	if (line[i + y] == '?' || ft_isdigit(line[i + y]))
		y++;
	ft_strcat(final, &line[i + y]);
	free(line);
	return (final);
}

void	update_quote_2(char *line, int i)
{
	line[i] = '\0';
	ft_strcat(line, &line[i + 2]);
}

void	ft_update_quote(char *line)
{
	int		simple_quote;
	int		double_quote;
	int		i;

	i = 0;
	simple_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !is_escaped(line, i - 1))
		{
			simple_quote++;
			if (line[i + 1] == '\'' && simple_quote % 2 == 1)
				update_quote_2(line, i);
		}
		if (line[i] == '\"' && !is_escaped(line, i - 1))
		{
			double_quote++;
			if (line[i + 1] == '\"' && double_quote % 2 == 1)
				update_quote_2(line, i);
		}
		i++;
	}
}

char	*ft_update_variable_2(char *line, t_env *envir)
{
	int		i;
	int		s_quote;

	if (!line)
		return (line);
	i = -1;
	s_quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && !is_escaped(line, i - 1))
			s_quote++;
		if (line[i] == '$' && line[i + 1] != '=' && line[i + 1] != '\"'
		&& line[i + 1] && !is_escaped(line, i - 1) && !(s_quote % 2))
		{
			line = update_line(line, i, envir);
			i = -1;
			s_quote = 0;
		}
	}
	return (line);
}

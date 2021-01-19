/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:02:45 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 12:14:59 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_valid_quote_nb(char *cmd)
{
	int	s_quote;
	int	d_quote;
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && !(d_quote % 2) &&
		(s_quote % 2 || !is_escaped(cmd, i - 1)))
			s_quote++;
		else if (cmd[i] == '\"' && !is_escaped(cmd, i - 1) && !(s_quote % 2))
			d_quote++;
		i++;
	}
	if (s_quote % 2 != 0 || (d_quote % 2 != 0))
		return (0);
	return (1);
}

char	*return_tronc(char *line, int begin, int len)
{
	if (line[begin] == '?')
		return (ft_strdup("?"));
	else
		return (ft_substr(line, begin, len));
}

char	*update_line(char *line, int i, t_env *envir)
{
	char	*final;
	int		len_final;
	int		y;
	char	*tronc;

	y = 1;
	while (line[i + y] && !ft_strchr("$ =\"\'?\\", line[i + y]) &&
		!ft_isdigit(line[i + y]))
		y++;
	tronc = return_tronc(line, i + 1, y - 1);
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

char	*ft_update_variable(char *line, t_env *envir)
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

char	**devide_cmd(char *cmd)
{
	char	**parsed;
	int		i;
	int		word[2];

	if (!(parsed = malloc(sizeof(*parsed) * (ft_count_word(cmd) + 1))))
		return (NULL);
	i = 0;
	word[0] = 0;
	while (cmd[i])
	{
		word[1] = i;
		i = go_to_end_word(i, cmd);
		parsed[word[0]++] = ft_substr(cmd, word[1], i - word[1]);
		i += ((cmd[i]) ? 1 : 0);
		i = pass_whitespaces(cmd, i);
	}
	parsed[word[0]] = NULL;
	return (parsed);
}

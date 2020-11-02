/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:21:29 by frchaban          #+#    #+#             */
/*   Updated: 2020/10/06 12:24:04 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			check_valid_quote_nb(char *cmd)
{
	int 	nb_simple_quote;
	int		nb_double_quote;
	int		i;

	if (!cmd)
		return (0);
	i = 0;
	nb_simple_quote = 0;
	nb_double_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && (!i || cmd[i - 1] != '\\'))
			nb_simple_quote++;
		if (cmd[i] == '\"' && (!i || cmd[i - 1] != '\\'))
			nb_double_quote++;
		i++;
	}
	if (nb_simple_quote % 2 != 0 || (nb_double_quote % 2 != 0))
		return (0);
	return (1);	
}

char	**parse_cmd(char **cmd)
{
	*cmd = ft_strtrim_freed(*cmd, " \t");
	if (!check_valid_quote_nb(*cmd))
		return (NULL);
	else
		return (ft_parse_cmd(*cmd));
}

int			ft_count_word(char *cmd)
{
	int		i;
	char	*end_next_word;
	int		word_nb;

	i =	0;
	word_nb = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (cmd[i] == '\'' || cmd[i] == '\"')
			end_next_word = ft_substr(&cmd[i], 0, 1);
		else
			end_next_word = ft_strdup(" \t");
		if (cmd[i])
			i++;
		while (!ft_strchr(end_next_word, cmd[i]) && cmd[i])
			i++;
		word_nb++;
		free(end_next_word);
		if (cmd[i])
			i++;
	}
	return (word_nb);
}

char		**ft_parse_cmd(char *cmd)
{
	char	**parsed;
	int		i;
	int		word_begin;
	char	*end_next_word;
	int		word_nb;

	if (!(parsed = malloc(sizeof(*parsed) * (ft_count_word(cmd) + 1))))
		return (NULL);
	i =	0;
	word_nb = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		end_next_word = (cmd[i] == '\'' || cmd[i] == '\"') ?
		ft_substr(&cmd[i], 0, 1) : ft_strdup(" \t");
		word_begin = (cmd[i] == '\'' || cmd[i] == '\"') ? ++i : i++;
		while (!ft_strchr(end_next_word, cmd[i]) && cmd[i])
			i++;
		parsed[word_nb++] = ft_substr(cmd, word_begin, i - word_begin);
		i += ((cmd[i]) ? 1 : 0); 
		free(end_next_word);
	}
	parsed[word_nb] = NULL;
	return (parsed);
}

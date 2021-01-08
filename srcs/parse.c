/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:21:29 by frchaban          #+#    #+#             */
/*   Updated: 2021/01/06 21:28:18 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		line[i] == '\'' ? simple++ : 0;
		line[i] == '\"' ? double_q++ : 0;
		if (line[i] == c && (simple % 2 || double_q % 2 ||
		is_escaped(line, i - 1)))
			line[i] = 7;
	}
	return (put_back_character(line, c));
}

char	**parse_cmd(char **cmd, t_env *envir)
{
	*cmd = ft_strtrim_freed(*cmd, " \t");
	*cmd = ft_update_variable_2(*cmd, envir);
	if (!check_valid_quote_nb(*cmd))
		return (NULL);
	else
		return (ft_parse_cmd(*cmd));
}

int		ft_count_word(char *cmd)
{
	int		i;
	char	*end_next_word;
	int		word_nb;

	i = 0;
	word_nb = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !is_escaped(cmd, i - 1))
			end_next_word = ft_substr(&cmd[i], 0, 1);
		else
			end_next_word = ft_strdup(" \t\'\"");
		if (cmd[i])
			i++;
		while (!word_end(i, cmd, end_next_word) && cmd[i])
			i++;
		word_nb++;
		free(end_next_word);
		if (cmd[i])
			i++;
	}
	ft_printf("word_nb = %d\n", word_nb);
	return (word_nb);
}

char	**ft_parse_cmd(char *cmd)
{
	char	**parsed;
	int		i;
	int		word[2];
	char	*end_next_word;

	handle_backslash_and_begin_quote(cmd);
	if (!(parsed = malloc(sizeof(*parsed) * (ft_count_word(cmd) + 1))))
		return (NULL);
	i = 0;
	word[0] = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !is_escaped(cmd, i - 1))
			end_next_word = ft_substr(&cmd[i], 0, 1);
		else
			end_next_word = ft_strdup(" \t\'\"");
		word[1] = i;
		while (cmd[++i] && !word_end(i, cmd, end_next_word))
			;
		parsed[word[0]++] = ft_substr(cmd, word[1], i - word[1]);
		//i += ((cmd[i]) ? 1 : 0);
		free(end_next_word);
	}
	//handle_backslash_and_begin_quote(cmd);
	parsed[word[0]] = NULL;
	ft_print_split(parsed);
	return (parsed);
}

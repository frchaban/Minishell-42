/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:21:29 by frchaban          #+#    #+#             */
/*   Updated: 2021/01/12 08:54:32 by gdupont          ###   ########.fr       */
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
		line[i] == '\'' && !is_escaped(line, i - 1) ? simple++ : 0;
		line[i] == '\"' && !is_escaped(line, i - 1) ? double_q++ : 0;
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

int		go_to_end_word(int i, char *cmd, char *end_word)
{
	char begin;

	begin = cmd[i];
	while (cmd[i])
	{
		if (ft_strchr(end_word, cmd[i]))
		{
			if ((cmd[i] == '\'' || cmd[i] == '\"') && is_escaped(cmd, i - 1))
				;
			else
				return (i);
		}
		i++;
	}
	if (begin != '\'' && begin != '\"')
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i--;
	return (i);
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
		// while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		// 	i++;
		if (cmd[i] == '\'' || cmd[i] == '\"')
			end_next_word = ft_substr(&cmd[i], 0, 1);
		else
			end_next_word = ft_strdup(" \t");
		i = go_to_end_word(i, cmd, end_next_word);
		word_nb++;
		free(end_next_word);
		if (cmd[i])
			i++;
	}
	return (word_nb);
}

// void	clean_quote(char *line, char *end_word)
// {
// 	int i;

// 	if (end_word[0] == '\'' || end_word[1] =='\"')
// 		return ;
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\"' || line[i] == '\'' )
// 	}
// }

void	handle_backslash_and_begin_quote_final(char *cmd)
{
	int i;
	int quote[2];

	i = -1;
	quote[0] = 0;
	quote[1] = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && !is_escaped(cmd, i - 1))
			quote[0] += 1;
		else if (cmd[i] == '\"' && !is_escaped(cmd, i - 1))
			quote[1] += 1;
		else if (cmd[i] == '\\' && !(quote[0] % 2) && !(quote[1] % 2)
		&& (cmd[i + 1] == '\"' || cmd[i + 1] == '\''))
		{
			//ft_printf("avant final:-%s-\n", cmd);
			ft_strcpy(&cmd[i], &cmd[i + 1]);
			//ft_printf("after final:-%s-\n", cmd);
		}
	}
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
		// while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
		// 	i++;
		end_next_word = (cmd[i] == '\'' || cmd[i] == '\"') ?
		ft_substr(&cmd[i], 0, 1) : ft_strdup(" \t");
		word[1] = (cmd[i] == '\'' || cmd[i] == '\"') ? ++i : i;
		i = go_to_end_word(i, cmd, end_next_word);
		parsed[word[0]++] = ft_substr(cmd, word[1], i - word[1]);
		//clean_quote(parsed[word[0] - 1], end_next_word);
		i += ((cmd[i]) ? 1 : 0);
		handle_backslash_and_begin_quote_final(parsed[word[0] - 1]);
		free(end_next_word);
	}
	parsed[word[0]] = NULL;
	ft_print_split(parsed);
	return (parsed);
}

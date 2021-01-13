/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:21:29 by frchaban          #+#    #+#             */
/*   Updated: 2021/01/13 14:49:20 by gdupont          ###   ########.fr       */
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

// int		go_to_end_word(int i, char *cmd, char **end_word)
// {
// 	char begin;

// 	begin = cmd[i];
// 	while (cmd[i])
// 	{
// 		if (ft_strchr(*end_word, cmd[i]))
// 		{
// 			if ((cmd[i] == S_QUOTE || cmd[i] == D_QUOTE) && 
// 			 !ft_strchr(" \t", cmd[i + 1]))
// 				{
// 					free(*end_word);
// 					if (cmd[i] == S_QUOTE || cmd[i] == D_QUOTE)
// 						*end_word = ft_substr(&cmd[i], 0, 1);
// 					else
// 						*end_word = ft_strdup(" \t");
// 				}
// 			else
// 			{
// 				if ((cmd[i] == S_QUOTE || cmd[i] == D_QUOTE))
// 					i++;
// 				return (i);
// 			}
// 		}
// 		i++;
// 	}
// 	return (i);
// }

int		go_to_end_word(int i, char *cmd)
{
	int s_quote;
	int d_quote;

	s_quote = 0;
	d_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && !(d_quote % 2) && 
		(s_quote % 2 || !is_escaped(cmd, i - 1)))
			s_quote++;
		else if (cmd[i] == '\"' && !is_escaped(cmd, i - 1) && !(s_quote % 2))
			d_quote++;
		else if (ft_strchr(" \t", cmd[i]) && !(s_quote % 2) && !(d_quote % 2))
			return (i);
		i++;
	}
	return (i);
}

int		ft_count_word(char *cmd)
{
	int		i;
	int		word_nb;

	i = 0;
	word_nb = 0;
	while (cmd[i])
	{
		i = go_to_end_word(i, cmd);
		word_nb++;
		if (!cmd[i])
			return (word_nb);
		while (ft_strchr(" \t", cmd[i]))
			i++;
	}
	return (word_nb);
}

int		pass_whitespaces(char *line, int i)
{
	while (line[i] && ft_strchr(" \t", line[i]))
		i++;
	return (i);
}

// void	change_quote_values(char *cmd)
// {
// 	int	s_quote;
// 	int	d_quote;
// 	int	i;

// 	if (!cmd)
// 		return ;
// 	i = 0;
// 	s_quote = 0;
// 	d_quote = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'' && !is_escaped(cmd, i - 1) && !(d_quote % 2))
// 		{
// 			s_quote++;
// 			cmd[i] = S_QUOTE;
// 		}
// 		if (cmd[i] == '\"' && !is_escaped(cmd, i - 1) && !(s_quote % 2))
// 		{
// 			d_quote++;
// 			cmd[i] = D_QUOTE;
// 		}
// 		i++;
// 	}
// }

int		backslash_in_double_quote(char *cmd, int index)
{
	int d_quote;

	d_quote = index;
	while (cmd[d_quote])
	{
		if (cmd[d_quote] == '\"' && !is_escaped(cmd, d_quote - 1))
			break ;
		d_quote++;
	}
	while (cmd[index] && index != d_quote)
	{
		if (cmd[index] == '\\' && ft_strchr("$\"`m\\", cmd[index + 1]))
		{
			ft_strcpy(&cmd[index], &cmd[index + 1]); 
			d_quote--;
		}
		index++;	
	}
	ft_strcpy(&cmd[d_quote], &cmd[d_quote + 1]);
	return (--d_quote);
}

// void	handle_backslash(char **cmd, int *i, int *s_quote, int *d_quote)
// {
// 	char *cmd_def;

// 	cmd_def = *cmd;
// 	if (*s_quote % 2)
// 				;
// 	else if (*d_quote % 2)
// 	{
// 		*i = backslash_in_double_quote(*cmd, *i);
// 		*d_quote = 0;
// 		*cmd = &cmd_def[i + 1];
// 		*i = -1;
// 	}
// 	else
// 		ft_strcpy(&cmd_def[i], &cmd_def[i + 1]);
// }

void	get_through_and_clean_quote_and_backslash(char *cmd)
{
	int	s_quote;
	int d_quote;
	int i;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '\'' && !(d_quote % 2) && !is_escaped(cmd, i - 1))
		{
			s_quote++;
			ft_strcpy(&cmd[i], &cmd[i + 1]);
			i--;
		}
		else if (cmd[i] == '\"' && !is_escaped(cmd, i - 1) && !(s_quote % 2))
		{
			d_quote++;
			ft_strcpy(&cmd[i], &cmd[i + 1]);
			i--;
		}
		else if (cmd[i] == '\\')
		{
			//handle_backslash(&cmd, &i, &s_quote, &d_quote);
			if (s_quote % 2)
				;
			else if (d_quote % 2)
			{
				i = backslash_in_double_quote(cmd, i);
				d_quote = 0;
				cmd = &cmd[i + 1];
				i = -1;
			}
			else
				ft_strcpy(&cmd[i], &cmd[i + 1]);
		}
		i++;
	}
}

char	**ft_parse_cmd(char *cmd)
{
	char	**parsed;
	int		i;
	int		word[2];

	handle_quote(cmd);
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
		get_through_and_clean_quote_and_backslash(parsed[word[0] - 1]);
		//handle_backslash_and_begin_quote_final(parsed[word[0] - 1]);
	}
	parsed[word[0]] = NULL;
	ft_print_split(parsed);
	return (parsed);
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

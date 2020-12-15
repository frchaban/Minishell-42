/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:21:29 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/15 16:23:54 by user42           ###   ########.fr       */
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

char	*update_line(char *line, int i, t_env *envir)
{
	char	*final;
	int		len_final;
	int		y;
	char	*tronc;

	y = 1;
	while (line[i + y] && line[i + y] != '$' && line[i + y] != ' '
	 && line[i + y] != '=' && line[i + y] != '\"' &&
	 line[i + y] != '\'' && line[i + y - 1] != '?' && !ft_isdigit(line[i + y]))
		y++;
	tronc = ft_substr(line, i + 1, y);
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
		if (line[i] == '\'')
		{
			simple_quote++;
			if (line[i + 1] == '\'' && simple_quote % 2 == 1)
				update_quote_2(line, i);
		}
		if (line[i] == '\"')
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

	if (!line)
		return (line);
//	ft_putendl_fd(line, 1);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\\' && line[i + 1] == '$')
			i++;
		else if (line[i] == '$' && line[i + 1] != '=' && line[i + 1] != '\"' && line[i + 1])
			line = update_line(line, i--, envir);
		if (!line[i])
			break ;
	}
	ft_update_quote(line);
	//ft_putendl_fd(line, 1);
//	ft_putendl(line);
	return (line);
}

char	**parse_cmd(char **cmd, t_env *envir)
{
	*cmd = ft_strtrim_freed(*cmd, " \t");
	*cmd = ft_update_variable_2(*cmd, envir);
	//ft_putendl(*cmd);
	if (!check_valid_quote_nb(*cmd))
		return (NULL);
	else
		return (ft_parse_cmd(*cmd, envir));
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

char	**ft_parse_cmd(char *cmd, t_env *envir)
{
	char	**parsed;
	int		i;
	int		word_begin;
	char	*end_next_word;
	int		word_nb;

	(void)envir;
	if (!(parsed = malloc(sizeof(*parsed) * (ft_count_word(cmd) + 1))))
		return (NULL);
	i = 0;
	word_nb = 0;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		end_next_word = (cmd[i] == '\'' || cmd[i] == '\"') ?
		ft_substr(&cmd[i], 0, 1) : ft_strdup(" \t");
		word_begin = (cmd[i] == '\'' || cmd[i] == '\"') ? ++i : i;
		while (cmd[i] && !ft_strchr(end_next_word, cmd[i]))
			i++;
		parsed[word_nb++] = ft_substr(cmd, word_begin, i - word_begin);
		i += ((cmd[i]) ? 1 : 0);
		free(end_next_word);
	}
	parsed[word_nb] = NULL;
	return (parsed);
}

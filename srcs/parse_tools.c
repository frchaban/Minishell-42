/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 23:52:50 by gdupont           #+#    #+#             */
/*   Updated: 2021/01/19 12:18:50 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_escaped(char *cmd, int i)
{
	if ((unsigned int)i >= ft_strlen(cmd))
		return (0);
	if (i < 0)
		return (0);
	else if (cmd[i] != '\\')
		return (0);
	if (i == 0)
		return (1);
	if (is_escaped(cmd, i - 1))
		return (0);
	return (1);
}

int		word_end(int i, char *cmd, char *end_next_word)
{
	if (!ft_strchr(end_next_word, cmd[i]))
		return (1);
	else if (i == 0 && ft_strchr(end_next_word, cmd[i]))
		return (0);
	else if (ft_strchr(end_next_word, cmd[i]) && is_escaped(cmd, i - 1))
		return (1);
	return (0);
}

void	handle_quote(char *cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] != '\"' && cmd[i] != '\'')
			return ;
		else if (cmd[i + 1] == cmd[i])
			ft_strcpy(&cmd[i], &cmd[i + 2]);
	}
}

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
		else if (ft_strchr(" \t", cmd[i]) && !(s_quote % 2) && !(d_quote % 2)
		&& !is_escaped(cmd, i - 1))
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
		while (cmd[i] && ft_strchr(" \t", cmd[i]))
			i++;
	}
	return (word_nb);
}

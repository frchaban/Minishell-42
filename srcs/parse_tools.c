/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 23:52:50 by gdupont           #+#    #+#             */
/*   Updated: 2021/01/12 08:52:16 by gdupont          ###   ########.fr       */
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
	else if (ft_strchr(end_next_word, cmd[i]) && is_escaped(cmd, (i) - 1))
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
		{
			cmd[i] = ' ';
			cmd[++i] = ' ';
		}
	}
}

void	handle_backslash_and_begin_quote(char *cmd)
{
	int i;
	int quote[2];

	handle_quote(cmd);
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
		&& cmd[i + 1] != '\"' && cmd[i + 1] != '\''
		&& !ft_strchr(" \t", cmd[i + 1]))
		{
			ft_strcpy(&cmd[i], &cmd[i + 1]);
			//ft_printf("after :-%s-\n", cmd);
		}
	}
}

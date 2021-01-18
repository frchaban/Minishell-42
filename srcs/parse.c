/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:21:29 by frchaban          #+#    #+#             */
/*   Updated: 2021/01/18 20:27:27 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	handle_backslash(char **cmd, int *i, int *s_quote, int *d_quote)
{
	char *cmd_def;

	cmd_def = *cmd;
	if (*s_quote % 2)
		;
	else if (*d_quote % 2)
	{
		*i = backslash_in_double_quote(*cmd, *i);
		*d_quote = 0;
		*cmd = &cmd_def[*i + 1];
		*i = -1;
	}
	else
		ft_strcpy(&cmd_def[*i], &cmd_def[*i + 1]);
}

void	get_through_and_clean_quote_and_backslash(char *cmd)
{
	int	s_quote;
	int d_quote;
	int i;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (cmd[i])
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
			handle_backslash(&cmd, &i, &s_quote, &d_quote);
		i++;
	}
}

void	inspect_redirections(char *cmd)
{
	int s_quote;
	int d_quote;
	int i;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	g_redirections = 1;
	while (cmd[i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<') && ((s_quote % 2) ||
		(d_quote % 2) || is_escaped(cmd, i - 1)))
			g_redirections = 0;
		else if (cmd[i] == '\'' && !(d_quote % 2) && !is_escaped(cmd, i - 1))
			s_quote++;
		else if (cmd[i] == '\"' && !is_escaped(cmd, i - 1) && !(s_quote % 2))
			d_quote++;
		i++;
	}
}

char	**parse_cmd(char **cmd, t_env *envir)
{
	char	**parsed_cmd;
	int		i;

	*cmd = ft_strtrim_freed(*cmd, " \t");
	*cmd = ft_update_variable(*cmd, envir);
	if (!check_valid_quote_nb(*cmd))
		return (NULL);
	inspect_redirections(*cmd);
	handle_quote(*cmd);
	parsed_cmd = devide_cmd(*cmd);
	i = 0;
	while (parsed_cmd[i])
		get_through_and_clean_quote_and_backslash(parsed_cmd[i++]);
	return (parsed_cmd);
}

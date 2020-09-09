/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 12:21:29 by frchaban          #+#    #+#             */
/*   Updated: 2020/09/09 12:01:56 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *cmd)
{
	int ret;
	int i;

	ret = 1;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] && cmd[i] != '\"')
				i++;
			ret++;
		}
		else if ( cmd[i] == '\'')
		{
			i++;
			while (cmd[i] && cmd[i] != '\'')
				i++;
			ret++;
		}
		else if (cmd[i] == ' ' || cmd[i] == '\t' )
		{
			while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
				i++;
			while (cmd[i] && cmd[i] == ' ' && cmd[i] == '\t')
				i++;
			ret++;
		}
		else
			i++;
	}
	return (ret);
}

static int	ft_wordlen(char const *s, unsigned int pos, char c)
{
	unsigned int	i;

	i = 0;
	while (s[pos + i] && s[pos + i] != c)
		i++;
	return (i);
}

char **ft_parse_cmd(char *cmd)
{
	char	**parsed;
	int		cpt;
	int		i;
	int		len;

	if (!(parsed = malloc(sizeof(*parsed) * (count_words(cmd) + 1))))
		return (NULL);
	cpt = 0;
	i = 0;
	while (cmd[i])
	{	
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (!ft_strchr("\'\"\t ", cmd[i]))
		{
			len = (ft_wordlen(cmd, i, ' ') == 0 ? ft_wordlen(cmd, i, '\t') : ft_wordlen(cmd, i, ' '));
			parsed[cpt] = ft_substr(cmd, i, len);
			cpt++;
			i = i + len - 1;
		}
		else if (cmd[i] == '\'')
		{
			len = ft_wordlen(cmd, ++i, '\'');
			parsed[cpt] = ft_substr(cmd, i, len);
			cpt++;
			i = i + len - 1;
		}
		else if (cmd[i] == '\"')
		{
			len = ft_wordlen(cmd, ++i, '\"');
			parsed[cpt] = ft_substr(cmd, i, len);
			cpt++;
			i = i + len - 1;
		}
		i++;
	}
	parsed[cpt] = NULL;
	return (parsed);
}

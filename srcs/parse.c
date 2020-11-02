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

// static	int		count_words(char *cmd)
// {
// 	int ret;
// 	int i;

// 	ret = 1;
// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\"')
// 		{
// 			i++;
// 			while (cmd[i] && cmd[i] != '\"')
// 				i++;
// 			ret++;
// 		}
// 		else if (cmd[i] == '\'')
// 		{
// 			i++;
// 			while (cmd[i] && cmd[i] != '\'')
// 				i++;
// 			ret++;
// 		}
// 		else if (cmd[i] == ' ' || cmd[i] == '\t' )
// 		{
// 			while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
// 				i++;
// 			while (cmd[i] && cmd[i] == ' ' && cmd[i] == '\t')
// 				i++;
// 			ret++;
// 		}
// 		if (cmd[i])
// 			i++;
// 	}
// 	return (ret);
// }

void	clean_useless_quote(char *cmd)
{
	int i;
	int quote_nbr;

	i= -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\"' && i != 0 && cmd[i - 1] != '\\')
		{
			quote_nbr++;
			if (cmd[++i] == '\"' && (quote_nbr % 2) == 1)
			{
				quote_nbr = 0;
				cmd[i - 1] = ' ';
				cmd[i] = ' ';
			}
		}
	}
}

void	clean_useless_simple_quote(char *cmd)
{
	int i;
	int quote_nbr;

	i= -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && i != 0 && cmd[i - 1] != '\\')
		{
			quote_nbr++;
			if (cmd[++i] == '\'' && (quote_nbr % 2) == 1)
			{
				quote_nbr = 0;
				cmd[i - 1] = ' ';
				cmd[i] = ' ';
			}
		}
	}
}

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
	//clean_useless_quote(*cmd);
	//clean_useless_simple_quote(*cmd);
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
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			end_next_word = ft_substr(&cmd[i], 0, 1);
			word_begin = ++i;
		}
		else
		{
			end_next_word = ft_strdup(" \t");
			word_begin = i++;
		}
		while (!ft_strchr(end_next_word, cmd[i]) && cmd[i])
			i++;
		parsed[word_nb++] = ft_substr(cmd, word_begin, i - word_begin);
		if (cmd[i])
			i++;
		free(end_next_word);
	}
	parsed[word_nb] = NULL;
	ft_print_split(parsed);
	return (parsed);
}





	// while (cmd[i])
	// {	
	// 	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
	// 		i++;
	// 	if (!ft_strchr("\'\"\t ", cmd[i]))
	// 	{
	// 		len = (ft_wordlen(cmd, i, ' ') == 0 ? ft_wordlen(cmd, i, '\t') : ft_wordlen(cmd, i, ' '));
	// 		parsed[cpt] = ft_substr(cmd, i, len);
	// 		cpt++;
	// 		i = i + len - 1;
	// 	}
	// 	else if (cmd[i] == '\'')
	// 	{
	// 		len = ft_wordlen(cmd, ++i, '\'');
	// 		parsed[cpt] = ft_substr(cmd, i, len);
	// 		cpt++;
	// 		i = i + len - 1;
	// 	}
	// 	else if (cmd[i] == '\"')
	// 	{
	// 		len = ft_wordlen(cmd, ++i, '\"');
	// 		parsed[cpt] = ft_substr(cmd, i, len);
	// 		cpt++;
	// 		i = i + len - 1;
	// 	}
	// 	i++;
	// }
	// parsed[cpt] = NULL;

// 	return (parsed);
// }


/*
char		**ft_count_cmd(char *cmd)
{
	int		i;
	int		word_begin;
	char	*end_next_word;
	int		word_nb;

	i =	0;
	word_nb = 0;
	(void)word_begin;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (cmd[i] == '\'' && cmd[i] == '\"')
		{
			end_next_word = ft_strdup(&cmd[i]);
			word_begin = ++i;
		}
		else
		{
			end_next_word = ft_strdup(" \t");
			word_begin = i++;
		}
		ft_putnbr(i);
		while (!ft_strchr(end_next_word, cmd[i]) && cmd[i])
			i++;
		word_nb++;
		ft_putnbr(i);
	}
	return (NULL);
}
*/
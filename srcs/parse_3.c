/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:18:20 by gdupont           #+#    #+#             */
/*   Updated: 2021/01/19 14:39:03 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap(char **a, char **b)
{
	char *temp;

	temp = *a;
	*a = *b;
	*b = *a;
}

int		ft_size_of_2dim(char **s)
{
	int i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

void	swap_if_first_character_is_redir(char ***cmd_all)
{
	char	**cmd;
	char	**final;
	int		size;
	int		i;

	cmd = *cmd_all;
	size = ft_size_of_2dim(cmd) + 1;
	if (cmd[0][0] != '>' || !cmd[1] || !cmd[2])
		return ;
	if (!(final = malloc(sizeof(*final) * size)))
		return ;
	final[size - 1] = NULL;
	final[size - 3] = cmd[0];
	final[size - 2] = cmd[1];	
	i = 2;
	while (cmd[i])
	{
		final[i - 2] = cmd[i];
		i++;
	}
	free(*cmd_all);
	*cmd_all = final;
}

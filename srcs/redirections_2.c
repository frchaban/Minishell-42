/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:50:43 by user42            #+#    #+#             */
/*   Updated: 2020/12/16 17:22:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_cmd(char **cmd, int i, int flag)
{
	if (flag)
	{
		free(cmd[i]);
		if (cmd[i + 1])
		{
			free(cmd[i + 1]);
			cmd[i] = cmd[i + 2];
		}
		else
			cmd[i] = NULL;
		cmd[i + 1] = NULL;
	}
}

int		handle_min_sup(char **cmd, int i, int flag)
{
	int fd;

	if (ft_strequ(cmd[i], "<>") && cmd[i + 1] && !ft_strchr(cmd[i + 1], '>')
		&& !ft_strchr(cmd[i + 1], '<'))
	{
		if ((fd = open(cmd[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644)) < 0)
		{
			ft_error("minishell: syntax error near unexpected token `newline'",
			NULL, 2, NULL);
			flag == 1 ? exit(EXIT_FAILURE) : 0;
		}
		else
			close(fd);
		update_cmd(cmd, i, flag);
		return (1);
	}
	return (0);
}

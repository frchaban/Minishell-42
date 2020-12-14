/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:13:06 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/14 11:07:47 by user42           ###   ########.fr       */
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

int		ft_greater_redir(char **cmd, int i, int flag)
{
	int fd;

	if ((fd = open(cmd[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644)) < 0)
	{
		ft_error("minishell: syntax error near unexpected token `newline'",
		NULL, 2, NULL);
		flag == 1 ? exit(EXIT_FAILURE) : 0;
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	update_cmd(cmd, i, flag);
	return (fd);
}

int		ft_greatgreat_redir(char **cmd, int i, int flag)
{
	int fd;

	if ((fd = open(cmd[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644)) < 0)
	{
		ft_error("minishell: syntax error near unexpected token `newline'",
		NULL, 2, NULL);
		flag == 1 ? exit(EXIT_FAILURE) : 0;
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	update_cmd(cmd, i, flag);
	return (fd);
}

int		ft_lesser_redir(char **cmd, int i, int flag)
{
	int fd;

	if ((fd = open(cmd[i + 1], O_RDONLY, 0)) < 0)
	{
		ft_error("minishell: no such file or directory: ", NULL, 2, NULL);
		flag == 1 ? exit(EXIT_FAILURE) : 0;
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	update_cmd(cmd, i, flag);
	return (fd);
}

int		special_case(char **cmd, int i, int flag)
{
	if (((ft_strequ(cmd[i], ">>") || ft_strequ(cmd[i], "<<")) && !cmd[i + 1]) 
	|| ((ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<'))
	&& (ft_strchr(cmd[i + 1], '>') || ft_strchr(cmd[i + 1], '<'))))
	{
		ft_error("minishell: syntax error near unexpected token `newline'",
		NULL, 2, NULL);
		flag == 1 ? exit(EXIT_FAILURE) : 0;
		return (0);
	}
	return (1);

}

int		ft_redir(char **cmd, int flag)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (cmd[++i])
	{
		if (!special_case(cmd, i, flag))
		 	return (-1);
		else if (ft_strequ(cmd[i], ">"))
			res = ft_greater_redir(cmd, i, flag);
		else if (ft_strequ(cmd[i], ">>"))
			res = ft_greatgreat_redir(cmd, i, flag);
		else if (ft_strequ(cmd[i], "<"))
			res = ft_lesser_redir(cmd, i, flag);
	}
	return (res);
}

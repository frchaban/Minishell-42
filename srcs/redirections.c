/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:13:06 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/09 17:00:37 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_greater_redir(char **cmd, int i)
{
	int fd;

	cmd[i] = NULL;
	if ((fd = open(cmd[++i],O_CREAT| O_RDWR | O_TRUNC,0644)) < 0)
	{
		ft_error("minishell: no such file or directory: ", NULL, cmd[i]);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd,STDOUT_FILENO);
		close (fd);
	}
	return (1);
}

int		ft_greatgreat_redir(char **cmd, int i)
{
	int fd;

	cmd[i] = NULL;
	if ((fd = open(cmd[++i],O_CREAT| O_RDWR | O_APPEND,0644)) < 0)
	{
		ft_error("minishell: no such file or directory: ", NULL, cmd[i]);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd,STDOUT_FILENO);
		close (fd);
	}
	return (1);
}

int		ft_lesser_redir(char **cmd, int i)
{
	int fd;

	cmd[i] = NULL;
	if ((fd = open(cmd[++i],O_RDONLY,0)) < 0)
	{
		ft_error("minishell: no such file or directory: ", NULL, cmd[i]);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd,STDIN_FILENO);
		close (fd);
	}
	return (1);
}

int		ft_redir(char **cmd)
{
	int i;

	i = -1;
	while(cmd[++i])
	{
		if (ft_strequ(cmd[i],">"))
			ft_greater_redir(cmd, i++);
		else if (ft_strequ(cmd[i],">>"))
			ft_greatgreat_redir(cmd, i++);
		else if (ft_strequ(cmd[i],"<"))
			ft_lesser_redir(cmd, i++);
	}
	return (1);
}

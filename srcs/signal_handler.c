/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:05:02 by frchaban          #+#    #+#             */
/*   Updated: 2020/10/28 15:27:33 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_ctrl_c(void)
{
	ft_putstr("\nminishell $>");
	errno = 1;
}

void	signal_ctrl_back_exit(void)
{
	kill(-1, SIGINT);
	ft_putchar('\n');
}

void	signal_ctrl_back_nothing(void)
{
	return ;
}

void	remove_ctrl(char *arg1, char *arg2, t_env *envir)
{
	int		status;
	pid_t	pid;
	char	**cmd;

	cmd = ft_split_freed(ft_strjoin(arg1, arg2), ' ');
	cmd[0] = get_absolute_path(cmd[0], envir);
	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		ft_error("Fork attempt failed", NULL, 1, envir);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0)
	{
		execve(cmd[0], cmd, NULL) == -1 ? ft_error("minishell: ",
		strerror(errno), errno, envir) : 0;
		exit(EXIT_FAILURE);
	}
	ft_free_2dim(cmd);
}

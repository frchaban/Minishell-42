/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:40:02 by gdupont           #+#    #+#             */
/*   Updated: 2021/01/18 20:41:03 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	call_next_cmd(char **cmd_split, char **cmd, int *status, t_env *envir)
{
	int		next_fd[3];
	pid_t	pid_fork;

	if (pipe(next_fd) == -1)
		exit(errno);
	if ((pid_fork = fork()) == -1)
		exit(errno);
	else if (pid_fork == 0)
	{
		close(next_fd[0]);
		dup2(next_fd[1], STDOUT_FILENO);
		launch(cmd, status, envir);
		exit(errno);
	}
	else
	{
		close(next_fd[1]);
		pipe_cmd(cmd_split + 1, next_fd, status, envir);
		ft_free_2dim(cmd);
	}
}

void	launch_in_fork(char **cmd, int *status, t_env *envir)
{
	pid_t	pid_fork;
	int		pid_status;

	if ((pid_fork = fork()) == -1)
		exit(errno);
	else if (pid_fork == 0)
	{
		launch(cmd, status, envir);
		exit(errno);
	}
	else
	{
		waitpid(pid_fork, &pid_status, 0);
		ft_free_2dim(cmd);
	}
}

void	pipe_cmd(char **cmd_split, int *previous_fd, int *status, t_env *envir)
{
	char		**cmd;

	cmd = parse_cmd(&cmd_split[0], envir);
	if (previous_fd)
		dup2(previous_fd[0], STDIN_FILENO);
	if (cmd_split[1])
		call_next_cmd(cmd_split, cmd, status, envir);
	else if (previous_fd)
		launch_in_fork(cmd, status, envir);
	else
		launch(cmd, status, envir);
}

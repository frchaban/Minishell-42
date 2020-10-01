/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:40:02 by gdupont           #+#    #+#             */
/*   Updated: 2020/10/01 15:48:46 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	pipe_cmd(char **cmd_split, int *previous_fd, int *status, t_env *envir)
{
	int		next_fd[2];
	pid_t	pid_fork;
	char	**cmd;

	cmd = parse_cmd(cmd_split[0]);
	if (previous_fd)
	dup2(previous_fd[0], 0);
	if (cmd_split[1])
	{
		pipe(next_fd);	//add security
		pid_fork = fork();
		if (pid_fork == 0)  
		{
			close(next_fd[0]);
			dup2(next_fd[1], 1);
			launch(cmd_semicolon[0], status, envir);
		}
		else
		{
			close(next_fd[1]);
			pipe_cmd(cmd_split + 1, next_fd, status, envir);
		}
	}
	else
		launch(cmd_semicolon[0], status, envir);
}

// void 	pipe_cmd(char **cmd_split, int *previous_fd, int *status, t_env *envir)
// {
// 	int		next_fd[2];
// 	pid_t	pid_fork;
// 	char	***cmd_semicolon;

// 	cmd_semicolon = parse_cmd(cmd_split[0]);
// 	if (!previous_fd) // if it is the first cmd
// 	{
// 		if (cmd_split + 1) // and there is another cmd
// 		{
// 			pipe(next_fd);	//add security
// 			pid_fork = fork();
// 			if (pid_fork == 0)  //child process
// 			{
// 				close(next_fd[0]);
// 				dup2(next_fd[1], 1);
// 				close(next_fd[1]);
// 				launch(cmd_semicolon[0], status, envir);
// 			}
// 			else
// 			{
// 				close(next_fd[1]);
// 				pipe_cmd(cmd_split + 1, next_fd, status, envir);
// 				write(1, "ok\n", 3);
// 				close(next_fd[0]);
// 			}
// 		}
// 		else
// 		{
// 			launch(cmd_semicolon[0], status, envir);
// 		}
// 	}
// 	else
// 	{
// 		close(previous_fd[1]);
// 		dup2(previous_fd[0], 0);
// 		close(previous_fd[0]);
// 		if (cmd_split[1]) // if there is a next cmd
// 		{
// 			pipe(next_fd);	//add security
// 			pid_fork = fork();
// 			if (pid_fork == 0)
// 			{
// 				close(next_fd[0]);
// 				dup2(next_fd[1], 0);
// 				close(next_fd[1]);
// 				launch(cmd_semicolon[0], status, envir);
// 				kill(pid_fork, 0);
// 			}
// 			else
// 			{
// 				close(next_fd[1]);
// 				pipe_cmd(cmd_split + 1, next_fd, status, envir);
// 				close(next_fd[0]);
// 				kill(pid_fork, 0);
// 			}
// 		}
// 		else
// 		{
// 			launch(cmd_split, status, envir);
// 		}
// 	}
// }
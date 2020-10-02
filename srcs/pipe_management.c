/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:40:02 by gdupont           #+#    #+#             */
/*   Updated: 2020/10/02 11:59:48 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	pipe_cmd(char **cmd_split, int *previous_fd, int *status, t_env *envir)
{
	int		next_fd[3];
	pid_t	pid_fork;
	char	**cmd;

	cmd = parse_cmd(cmd_split[0]);
	if (previous_fd)
		dup2(previous_fd[0], 0);
	if (cmd_split[1])
	{
		pipe(next_fd);	//add security
		if ((pid_fork = fork()) == -1)
			exit(1);
		else if (pid_fork == 0)  
		{
			close(next_fd[0]);
			dup2(next_fd[1], 1);
			launch(cmd, status, envir);
		}
		else
		{
			close(next_fd[1]);
			waitpid(pid_fork, &next_fd[2], 0);
			pipe_cmd(cmd_split + 1, next_fd, status, envir);
		}
	}
	else
		launch(cmd, status, envir);
}

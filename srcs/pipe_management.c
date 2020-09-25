/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:40:02 by gdupont           #+#    #+#             */
/*   Updated: 2020/09/25 15:32:20 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	pipe_cmd(char **cmd_split, int *previous_fd, int *status, t_env *envir)
{
	int		next_fd[2];
	pid_t	pid_fork;
	char	***cmd_semicolon;
	int		keep_fd;
	//char	**cmd;
	int		i[3];

	
//	cmd = ft_split(*cmd_split, ' ');
	cmd_semicolon = parse_cmd(cmd_split[0]);
	i[0] = 0;
	i[1] = 0;
	// while (cmd_semicolon[i[0]])
	// {
	// 		i[1] = 0;
	// 		while (cmd_semicolon[i[0]][i[1]])
	// 		{
	// 			ft_putstr(cmd_semicolon[i[0]][i[1]]);
	// 			write(1, "|\n", 2);
	// 			i[1]++;
	// 		}
	// 		puts("");
	// 	i[0]++;
	// }
	
	if (previous_fd)
	{
		keep_fd = dup(0);
		dup2(previous_fd[0], 0);
		close(previous_fd[0]);
		if (cmd_split[1])
		{
			pipe(next_fd);	//add security
			pid_fork = fork();
			if (pid_fork == 0)  
			{
				close(next_fd[1]);
				pipe_cmd(cmd_split + 1, next_fd, status, envir);
				kill(pid_fork, 0);
			}
			else
			{
				close(next_fd[0]);
				dup2(next_fd[1], 1);
				close(next_fd[1]);
				//execvp(*cmd, cmd);
				launch(cmd_semicolon[0], status, envir);
			}
		}
		else
		{
			//execvp(*cmd, cmd);
			launch(cmd_split, status, envir);
		}
		close(previous_fd[0]);
	}
	else
	{
		if (cmd_split[1])
		{
			pipe(next_fd);	//add security
			pid_fork = fork();
			if (pid_fork == 0)  
			{
				close(next_fd[1]);
				pipe_cmd(cmd_split + 1, next_fd, status, envir);
				kill(pid_fork, 0);
			}
			else
			{
				close(next_fd[0]);
				dup2(next_fd[1], 1);
				close(next_fd[1]);
				//execvp(*cmd, cmd);
				launch(cmd_semicolon[0], status, envir);
			}
		}
		else
		{
			//execvp(*cmd, cmd);
			launch(cmd_semicolon[0], status, envir);
		}
	}
	//dup2(keep_fd, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:40:02 by gdupont           #+#    #+#             */
/*   Updated: 2020/09/30 15:42:30 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	set_pipe(char **cmd_split, int *status, t_env *envir)
{
	char	***all_cmd;
	int i;
	int y;
	int	**all_pipe;
	pid_t	pid;
	int stt;

	all_cmd = parse_cmd(cmd_split);
	i = -1;
	if (!(all_pipe = malloc(sizeof(*all_pipe) * (ft_count_3dim(all_cmd)))))
		return ;
	y = -1;
	while (all_pipe[++y])
	{
		if (!(all_pipe[y] = malloc(sizeof(**all_pipe) * 2)))
			return ;
		pipe(all_pipe[y]);
	}
	all_pipe[y] = NULL;
	y = 0;
	launch(all_cmd[i], status, envir, 0);

	}
//fork_and_pipe(all_cmd[i], status, envir);
}

// void	fork_and_pipe(char **command_set, int *status, t_env *envir)
// {


// 	launch(all_cmd[i], status, envir, 0);
// }


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


// void 	set_pipe(char **cmd_split, int *status, t_env *envir)
// {
// 	char	***all_cmd;
// 	int i;
// 	int y;
// 	int	**all_pipe;

// 	all_cmd = parse_cmd(cmd_split);
// 	i = -1;
// 	if (!(all_pipe = malloc(sizeof(*all_pipe) * (ft_count_3dim(all_cmd)))))
// 		return ;
// 	y = -1;
// 	while (all_pipe[++y])
// 	{
// 		if (!(all_pipe[y] = malloc(sizeof(**all_pipe) * 2)))
// 			return ;
// 		pipe(all_pipe[y]);
// 	}
// 	all_pipe[y] = NULL;
// 	while (all_cmd[++i])
// 	{

// 		launch(all_cmd[i], status, envir, 0);
		
// 	}
	// cmd_semicolon = parse_cmd(cmd_split[0]);
	// states = 0;
	// if (previous_fd)
	// {
	// 	dup2(previous_fd[0], 0);
	// 	if (cmd_split[1])
	// 	{
	// 		pipe(next_fd);	//add security
	// 		pid_fork = fork();
	// 		if (pid_fork == 0)  
	// 		{
	// 			close(next_fd[1]);
	// 			pipe_cmd(cmd_split + 1, next_fd, status, envir);
	// 			exit(1);
	// 		}
	// 		else
	// 		{
	// 			close(next_fd[0]);
	// 			dup2(next_fd[1], 1);
	// 			close(next_fd[1]);
	// 			waitpid(pid_fork, &states, 1);
	// 			launch(cmd_semicolon[0], status, envir, 0);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		launch(cmd_semicolon[0], status, envir, 1);
	// 	}
	// }
	// else
	// {
	// 	if (cmd_split[1])
	// 	{
	// 		pipe(next_fd);	//add security
	// 		pid_fork = fork();
	// 		if (pid_fork == 0)  
	// 		{
	// 			close(next_fd[1]);
	// 			close(0);
	// 			pipe_cmd(cmd_split + 1, next_fd, status, envir);
	// 			exit(1);
	// 		}
	// 		else
	// 		{
	// 			close(next_fd[0]);
	// 			dup2(next_fd[1], 1);
	// 			close(next_fd[1]);
	// 			waitpid(pid_fork, &states, 1);
	// 			launch(cmd_semicolon[0], status, envir, 0);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		launch(cmd_semicolon[0], status, envir, 1);
	// 	}
	// }



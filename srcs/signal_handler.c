/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:05:02 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/11 14:43:20 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrl_c(void)
{
	ft_printf("\nminishell $> ");
}
//stty -echoctl

void	remove_ctrl(char *arg1, char *arg2, t_env *envir)
{
	int		status;
	pid_t	pid;
	char 	**cmd;

	cmd = ft_split_freed(ft_strjoin(arg1, arg2), ' ');
	cmd[0] = get_absolute_path(cmd[0], envir);
	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		ft_printf("%s\n", strerror(errno)) ; // error to manage
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else if (pid == 0)
	{
		execve(cmd[0], cmd, NULL) == -1 ? ft_error("minishell: ", strerror(errno) ,cmd[0]) : 0;
		exit(EXIT_FAILURE);
	}
	ft_free_2dim(cmd);
}

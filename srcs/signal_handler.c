/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:05:02 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/16 16:31:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_ctrl_c(void)
{
	G_PRINT_PROMPT = 0;
	ft_putstr_fd("\nminishell $>", 2);
	errno = 1;
}

void	signal_ctrl_back_exit(void)
{
	errno = 131;
	ft_putchar('\n');
	kill(-1, SIGABRT);
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

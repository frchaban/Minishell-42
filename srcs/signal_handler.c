/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:05:02 by frchaban          #+#    #+#             */
/*   Updated: 2021/01/14 10:31:55 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_ctrl_c(int signal)
{
	(void)signal;
	g_print_prompt = 0;
	g_ctrl_c = 1;
	ft_putstr_fd("\nminishell $>", 2);
	errno = 1;
}

void	signal_ctrl_back_nothing(int signal)
{
	(void)signal;
	ft_putstr_fd("\b\b  \b\b", 2);
}

void	ft_sigquit(int sig)
{
	g_ctrl_backslash = 1;
	ft_putstr_fd("Quit : ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putchar_fd('\n', 2);
}

void	adjust_errno_sigquit(t_env *envir)
{
	g_ctrl_backslash = 0;
	errno = 131;
	free(envir->content);
	envir->content = ft_itoa(errno);
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

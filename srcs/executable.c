/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:59:59 by user42            #+#    #+#             */
/*   Updated: 2020/12/15 17:07:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_parent(char **cmd, pid_t fork_pid, int *status)
{
	signal(SIGQUIT, signal_ctrl_back_nothing);
	ft_free_2dim(cmd);
	waitpid(fork_pid, status, 0);
	if (WIFEXITED(*status))
		errno = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		errno = WTERMSIG(*status);
}

void	ft_exit_command_not_found(char **cmd, t_env *envir)
{
	ft_error("minishell: command not found: ", cmd[0], 127, envir);
	ft_free_2dim(cmd);
	exit(127);
}

void	ft_exit_error(char **cmd, t_env *envir)
{
	char	error_msg[100];

	error_msg[0] = '\0';
	ft_strcat(error_msg, "minishell: ");
	ft_strcat(error_msg, strerror(errno));
	ft_strcat(error_msg, " : ");
	ft_error(error_msg, cmd[0], errno, envir);
	ft_free_2dim(cmd);
	exit(errno);
}

void	execute(char **cmd, t_env *envir)
{
	char	**env;
	pid_t	fork_pid;
	int		status;

	env = NULL;
	cmd[0] = get_absolute_path(cmd[0], envir);
	status = 0;
	signal(SIGQUIT, signal_ctrl_back_nothing);
	if ((fork_pid = fork()) == -1)
		exit(2);
	else if (fork_pid == 0)
	{
		signal(SIGQUIT, signal_ctrl_back_exit);
		if (ft_strchr(cmd[0], '/') == 0 && ft_strncmp(cmd[0], "./", 2) != 0)
			ft_exit_command_not_found(cmd, envir);
		env = list_to_envp(envir);
		ft_redir(cmd, 1);
		if (execve(cmd[0], cmd, env) == -1)
			ft_exit_error(cmd, envir);
	}
	else
		execute_parent(cmd, fork_pid, &status);
}

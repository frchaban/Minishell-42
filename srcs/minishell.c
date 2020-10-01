/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/10/01 18:09:56 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_error(char *error, char *error_errno, char *cmd)
{
	ft_putstr_fd(error, 2);
	if (error_errno != NULL)
	{
		ft_putstr_fd(error_errno, 2);
		ft_putstr_fd(": ", 2);
	}
	if (cmd != NULL)
		ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
}

void	check_cmd_exit(char **cmd, int *status)
{
	int i;
	char **cmd_cleaned;

	i = 0;
	while(cmd[i + 1])
		i++;
	cmd_cleaned = parse_cmd(cmd[i]);
	if (ft_strequ(cmd_cleaned[0], "exit"))
		*status = 0;
}

void	main_2(int *status, char *line, t_env *envir)
{
	char	**semicolon_split;
	char	**cmd;
	pid_t	pid;
	int 	stt;
	int i;

	if (!line || !line[0])
		return ;
	semicolon_split = ft_split(line, ';');
	i = 0;
	while (semicolon_split[i])
	{
		cmd = ft_split(semicolon_split[i++], '|');
		pid = fork();
		stt = 0;
		if (pid == 0)
		{
			pipe_cmd(cmd, NULL, status, envir);
			exit(1);
		}
		else
			waitpid(pid, &stt, 0);
		check_cmd_exit(cmd, status);
		free(cmd);
	}
	ft_free_2dim(semicolon_split);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	int	status;
	t_env	*envir;

	(void)argv;
	if (argc != 1)
		return (0);
	envp_to_list(&envir, env);
	remove_ctrl("stty", " -echoctl", envir);
	status = 1;
	while (status)
	{
		line = get_cmd();
		main_2(&status, line, envir);
		free(line);
	}
	free_all_list(envir);
	return (0);
}

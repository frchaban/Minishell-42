/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/10/05 14:34:50 by gdupont          ###   ########.fr       */
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

void	check_last_cmd(char **cmds, int *status, t_env *envir)
{
	int		i;
	char	**cmd;
	t_list	*args;
	int		save_fdout;

	i = 0;
	while (cmds[i + 1])
		i++;
	cmd = parse_cmd(cmds[i]);
	save_fdout = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	args = NULL;
	if (cmd[1])
		args_to_list(&args, cmd);
	if (ft_strcmp(cmd[0], "export") == 0)
		export_builtin(envir, args);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		echo_builtin(args);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd_builtin(args, envir);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd_builtin(args);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return unset_builtin(args, envir);
	else if (ft_strcmp(cmd[0], "env") == 0)
		env_builtin(envir);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		*status = exit_builtin();
	else if (ft_strchr(cmd[0], '='))
		variable_update(cmd[0], args, envir);
	free_args_list(args);
	dup2(save_fdout, STDOUT_FILENO);
	close(save_fdout);
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
		check_last_cmd(cmd, status, envir);
		free(cmd);
	}
	ft_free_2dim(semicolon_split);
}


int		check_cat_ctrl_c_case(char *line)
{
	char *cp;

	if (!(cp = malloc(sizeof(*cp) * (ft_strlen(line) + 1))))
		return (-1);
	ft_strcpy(cp, line);
	cp = ft_strtrim_freed(cp, " \t");
	if (ft_strequ(cp, "cat") == 1)
	{
		free(cp);
		return (0);
	}
	free(cp);
	return (1);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	int	status;
	t_env	*envir;
	int	print_prompt;

	(void)argv;
	print_prompt = 1;
	if (argc != 1)
		return (0);
	envp_to_list(&envir, env);
	remove_ctrl("stty", " -echoctl", envir);
	status = 1;
	while (status)
	{
		line = get_cmd(print_prompt);
		print_prompt = check_cat_ctrl_c_case(line);
		main_2(&status, line, envir);
		free(line);
	}
	free_all_list(envir);
	return (0);
}

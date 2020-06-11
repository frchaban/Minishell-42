/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:14:41 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/11 08:46:43 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**replace_var(char **cmd, t_env *envir)
{
	int i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i][0] == '$')
			cmd[i] = get_var_content(cmd[i], envir);
	}
	return (cmd);
}


char	***parse_cmd(char *line)
{
	char	**cmd;
	char	***data;
	int		i;

	i = -1;
	cmd = ft_split(line, ';');
	if (!(data = malloc(sizeof(*data) * (ft_count_split(cmd) + 1))))
		return (NULL);
	data[ft_count_split(cmd)] = NULL;
	while (cmd[++i])
	{
		cmd[i] = ft_strtrim_freed(cmd[i], " \t");
		data[i] = ft_parse_cmd(cmd[i]);
	}
	free(line);
	ft_free_2dim(cmd);
	return (data);
}

char	***get_cmd(void)
{
	char *line;

	ft_printf("%s", "minishell $> ");
	while (get_next_line(0, &line) != 1)
		;
	return (parse_cmd(line));
}

int		is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strchr(cmd, '='))
		return (1);
	return (0);
}

void	launch_builtin(char *cmd, t_list *args, t_env *envir, int *status)
{
	if (ft_strcmp(cmd, "export") == 0)
		export_builtin(envir, args);
	else if (ft_strcmp(cmd, "echo") == 0)
		echo_builtin(args);
	else if (ft_strcmp(cmd, "cd") == 0)
		cd_builtin(args, envir);
	else if (ft_strcmp(cmd, "pwd") == 0)
		pwd_builtin(args);
	else if (ft_strcmp(cmd, "unset") == 0)
		return unset_builtin(args, envir);
	else if (ft_strcmp(cmd, "env") == 0)
		env_builtin(envir);
	else if (ft_strcmp(cmd, "exit") == 0)
		*status = exit_builtin();
	else if (ft_strchr(cmd, '='))
		variable_update(cmd, args, envir);
}

void	launch(char **cmd, int *status, t_env *envir)
{
	t_list *args;
	int old_stdout;

	old_stdout = 0;
	cmd = replace_var(cmd, envir);
	if (is_builtin(cmd[0]) == 1)
	{
		old_stdout = dup(STDOUT_FILENO);
		if (ft_redir(cmd, 0) < 0)
			return ;
		args = NULL; 
		if (cmd[1])
			args_to_list(&args, cmd);
		launch_builtin(cmd[0], args, envir, status);
		free_args_list(args);
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdout);
	}
	else
		execute(cmd, envir);
}

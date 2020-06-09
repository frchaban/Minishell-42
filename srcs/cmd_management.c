/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:14:41 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/09 11:24:33 by frchaban         ###   ########.fr       */
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

void	prompt(void)
{
	ft_printf("%s", "minishell $> ");
}

char	***parse_cmd(char *line)
{
	char	**cmd;
	char	***data;
	int		i;
	int		j;

	i = -1;
	cmd = ft_split(line, ';');
	if (!(data = malloc(sizeof(*data) * (ft_count_split(cmd) + 1))))
		return (NULL);
	data[ft_count_split(cmd)] = NULL;
	while (cmd[++i])
	{
		cmd[i] = ft_strtrim_freed(cmd[i], " ");
		data[i] = ft_split(cmd[i], ' ');
		j = -1;
		while (data[i][++j])
			data[i][j] = ft_strtrim_freed(data[i][j], "\"\'");
	}
	free(line);
	ft_free_2dim(cmd);
	return (data);
}

char	***get_cmd(void)
{
	char *line;

	prompt();
	while (get_next_line(0, &line) != 1)
		;
	return (parse_cmd(line));
}

void	launch(char **cmd, int *status, t_env *envir)
{
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		export_builtin(envir, cmd);
		return;
	}
	cmd = replace_var(cmd, envir);
	if (ft_strcmp(cmd[0], "echo") == 0)
		echo_builtin(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd_builtin(cmd, envir);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd_builtin(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return ;
	else if (ft_strcmp(cmd[0], "env") == 0)
		env_builtin(envir, cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		*status = exit_builtin();
	else
		execute(cmd, envir);
}

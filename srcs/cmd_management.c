/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:14:41 by gdupont           #+#    #+#             */
/*   Updated: 2020/09/08 15:23:25 by gdupont          ###   ########.fr       */
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
		write(1, "replace\n", 8);
	}
	return (cmd);
}


char	***parse_cmd(char *line)
{
	char	**cmd;
	char	***data;
	int		i;
	int		len;

	i = -1;
	cmd = ft_split(line, ';');
	len = ft_count_split(cmd);
	if (!(data = malloc(sizeof(*data) * (len + 1))))
		return (NULL);
	data[len] = NULL;
	while (cmd[++i])
	{	
		ft_putendl(cmd[i]);
		cmd[i] = ft_strtrim_freed(cmd[i], " \t");	
		data[i] = ft_parse_cmd(cmd[i]);
		ft_print_split(data[i]);
		write(1, "limiter\n", 8);
	}
	free(line);
	ft_free_2dim(cmd);
	return (data);
}

char	*get_cmd(void)
{
	char *line;

	ft_printf("%s", "minishell $> ");
	signal(SIGINT,signal_ctrl_c);
	signal(SIGQUIT, signal_ctrl_back);
	while (get_next_line(0, &line) != 1)
		;
	return (line);
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
	t_list	*args;
	int		old_stdout;

	old_stdout = 0;
	cmd = replace_var(cmd, envir);
	if (is_builtin(cmd[0]) == 1)
	{
		old_stdout = dup(STDOUT_FILENO);
		if (ft_redir(cmd, 0) < 0)
			return ;
		args = NULL;
		if (cmd[1])
		{
			args_to_list(&args, cmd);
			write(1, "launch\n", 6);
		}
		launch_builtin(cmd[0], args, envir, status);
		free_args_list(args);
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdout);
	}
	else
		execute(cmd, envir);
}

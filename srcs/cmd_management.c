/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:14:41 by gdupont           #+#    #+#             */
/*   Updated: 2020/11/11 13:19:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**replace_var(char **cmd, t_env *envir)
{
	int i;

	i = -1;
	if (!cmd)
		return (NULL);
	while (cmd[++i])
	{
		if (cmd[i][0] == '$')
			cmd[i] = get_var_content(cmd[i], envir);
	}
	return (cmd);
}

void	ft_free_and_exit_ctrl_d(char *line, char *save)
{
	ft_putstr("exit\n");
	free(line);
	free(save);
	exit(0);
}

void	ft_free_double_str(char *temp, char *save)
{
	free(temp);
	free(save);
}

char	*get_cmd(int *print_prompt)
{
	char	*line;
	int		return_gnl;
	char	*save;
	char	*temp;

	if (*print_prompt)
		ft_putstr("minishell $>");
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, signal_ctrl_back_nothing);
	save = ft_strdup("");
	while ((return_gnl = get_next_line(0, &line)) != 1)
	{
		if (return_gnl == 0 && !line[0] && !save[0])
			ft_free_and_exit_ctrl_d(line, save);
		if (return_gnl == 0)
		{
			temp = save;
			save = ft_strjoin(save, line);
			free(temp);
		}
	}
	temp = line;
	line = ft_strjoin(save, line);
	ft_free_double_str(temp, save);
	return (line);
}

void	launch(char **cmd, int *status, t_env *envir)
{
	t_list	*args;
	int		old_stdout;

	old_stdout = 0;
	replace_var(cmd, envir);
	if (!cmd)
		return ;
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
		ft_free_2dim(cmd);
	}
	else if (cmd && *cmd)
		execute(cmd, envir);
	else if (cmd)
		free(cmd);
}

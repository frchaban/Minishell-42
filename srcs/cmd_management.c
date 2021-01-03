/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:14:41 by gdupont           #+#    #+#             */
/*   Updated: 2020/12/31 12:02:33 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	g_print_prompt = 1;
}

char	*get_cmd(void)
{
	char	*line;
	int		return_gnl;
	char	*save;
	char	*temp;

	if (g_print_prompt++)
		ft_putstr("minishell $>");
	signal(SIGINT, signal_ctrl_c);
	save = ft_strdup("");
	while ((return_gnl = get_next_line(0, &line)) != 1)
	{
		if (return_gnl == 0 && !line[0] && !save[0])
			ft_free_and_exit_ctrl_d(line, save);
		if (return_gnl == 0)
		{
			temp = save;
			save = ft_strjoin(save, line);
			ft_free_double_str(temp, line);
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
	if (!cmd)
		return ;
	if (is_builtin(cmd[0]) == 1)
	{
		old_stdout = dup(STDOUT_FILENO);
		if (ft_redir(cmd, 0) < 0)
			return (ft_free_2dim(cmd));
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

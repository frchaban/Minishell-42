/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2021/01/08 16:31:01 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_shlvl(t_env *envir)
{
	char	*to_free;

	while (envir)
	{
		if (ft_strequ(envir->key, "SHLVL"))
		{
			to_free = envir->content;
			envir->content = ft_itoa(ft_atoi(envir->content) + 1);
			free(to_free);
			break ;
		}
		envir = envir->next;
	}
}

void	launcher(int *status, char **line, t_env *envir)
{
	char	**semicolon_split;
	char	**cmd;
	int		i;
	int		save_fdout;
	int		save_fdin;

	if (!line || !(*line))
		return ;
	semicolon_split = handle_inside_quote_split(*line, ';');
	i = 0;
	while (semicolon_split[i])
	{
		save_fdout = dup(STDOUT_FILENO);
		save_fdin = dup(STDIN_FILENO);
		cmd = handle_inside_quote_split(semicolon_split[i++], '|');
		pipe_cmd(cmd, NULL, status, envir);
		ft_free_2dim(cmd);
		dup2(save_fdout, STDOUT_FILENO);
		dup2(save_fdin, STDIN_FILENO);
		close(save_fdout);
		close(save_fdin);
	}
	ft_free_2dim(semicolon_split);
}

void	minishell(int status, t_env *envir)
{
	char	*line;

	while (status)
	{
		if (g_ctrl_backslash)
			adjust_errno_sigquit(envir);
		line = get_cmd();
		check_double_semicolon(line, envir);
		check_hashtag(line);
		g_print_prompt = 1;
		launcher(&status, &line, envir);
		free(envir->content);
		envir->content = ft_itoa(errno);
		free(line);
	}
	free_all_list(envir);
}

int		main(int argc, char **argv, char **env)
{
	int		status;
	t_env	*envir;

	(void)argv;
	if (argc != 1)
		return (0);
	envp_to_list(&envir, env);
	update_shlvl(envir);
	remove_ctrl("stty", " echoctl", envir);
	status = 1;
	g_print_prompt = 1;
	g_ctrl_backslash = 0;
	signal(SIGQUIT, signal_ctrl_back_nothing);
	minishell(status, envir);
	return ((int)errno);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/16 17:18:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_cat_ctrl_c_case(char *line)
{
	char *cp;
	char **cp2;

	if (!(cp = malloc(sizeof(*cp) * (ft_strlen(line) + 1))))
		return (-1);
	ft_strcpy(cp, line);
	cp = ft_strtrim_freed(cp, " \t");
	if (!cp)
		return (1);
	cp2 = ft_split(cp, ' ');
	free(cp);
	if ((ft_strequ(cp2[0], "cat") == 1 && !cp2[1])
	|| ft_strequ(cp2[0], "yes") == 1)
	{
		ft_free_2dim(cp2);
		return (0);
	}
	ft_free_2dim(cp2);
	return (1);
}

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

void	main_2(int *status, char **line, t_env *envir)
{
	char	**semicolon_split;
	char	**cmd;
	int		i;
	int		save_fdout;
	int		save_fdin;

	if (!line || !(*line))
		return ;
	semicolon_split = ft_split(*line, ';');
	i = 0;
	while (semicolon_split[i])
	{
		save_fdout = dup(STDOUT_FILENO);
		save_fdin = dup(STDIN_FILENO);
		cmd = ft_split(semicolon_split[i++], '|');
		pipe_cmd(cmd, NULL, status, envir);
		ft_free_2dim(cmd);
		dup2(save_fdout, STDOUT_FILENO);
		dup2(save_fdin, STDIN_FILENO);
		close(save_fdout);
		close(save_fdin);
	}
	ft_free_2dim(semicolon_split);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	int		status;
	t_env	*envir;

	(void)argv;
	if (argc != 1)
		return (0);
	envp_to_list(&envir, env);
	update_shlvl(envir);
	remove_ctrl("stty", " echoctl", envir);
	status = 1;
	G_PRINT_PROMPT = 1;
	while (status)
	{
		line = get_cmd();
		G_PRINT_PROMPT = 1;
		main_2(&status, &line, envir);
		free(envir->content);
		envir->content = ft_itoa(errno);
		free(line);
	}
	free_all_list(envir);
	return ((int)errno);
}

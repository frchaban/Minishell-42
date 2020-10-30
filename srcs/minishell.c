/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/10/28 17:16:11 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_error(char *cmd_n_error_msg, char *arg, int error_nb, t_env *env)
{
	if (env)
	{
		free(env->content);
		env->content = ft_itoa(error_nb);
	}
	if (cmd_n_error_msg)
		ft_putstr_fd(cmd_n_error_msg, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
}

int		check_cat_ctrl_c_case(char *line)
{
	char *cp;
	char **cp2;

	if (!(cp = malloc(sizeof(*cp) * (ft_strlen(line) + 1))))
		return (-1);
	ft_strcpy(cp, line);
	cp = ft_strtrim_freed(cp, " \t");
	if (!cp || !cp[0])
		return (1);
	cp2 = ft_split(cp, ' ');
	free(cp);
	if ((ft_strequ(cp2[0], "cat") == 1 && !cp2[1]) || ft_strequ(cp2[0], "yes") == 1)
	{
		ft_free_2dim(cp2);
		return (0);
	}
	ft_free_2dim(cp2);
	return (1);
}

void	clean_line_from_empty_quote(char *line)
{
	int		i;
	int		save_index;

	i = 0;
	return ;
	ft_putnbr(ft_strlen(line));
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'') && line[i + 1])
		{
			save_index = i;
			i++;
			while (ft_is_whitespaces(line[i]))
				i++;
			if (line[save_index] == line[i])
			{
				ft_strcpy(&line[save_index + 1], &line[i]);
				i = save_index + 1;
			}
		}
		ft_putchar('-');
		ft_putchar(line[i]);
		ft_putchar('-');
		i++;
		ft_putnbr(i);
	}
}

void	main_2(int *status, char *line, t_env *envir)
{
	char	**semicolon_split;
	char	**cmd;
	int		i;
	int		save_fdout;
	int		save_fdin;

	if (!line || !line[0])
		return ;
	semicolon_split = ft_split(line, ';');
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

void	update_SHLVL(t_env *envir)
{
	char	*to_free;

	while(envir)
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
	update_SHLVL(envir);
	remove_ctrl("stty", " -echoctl", envir);
	status = 1;
	while (status)
	{
		line = get_cmd(&print_prompt);
		clean_line_from_empty_quote(line);
		clean_useless_quote(line);
		clean_useless_simple_quote(line);
		print_prompt = check_cat_ctrl_c_case(line);
		main_2(&status, line, envir);
		envir->content = ft_itoa(errno);
		free(line);
	}
	free_all_list(envir);
	return (0);
}

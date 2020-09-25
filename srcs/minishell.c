/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/09/25 15:55:36 by gdupont          ###   ########.fr       */
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

void	main_2(int *status, char *line, t_env *envir)
{

	char	**pipe_split;

	pipe_split = ft_split(line, '|');
	pipe_cmd(pipe_split, NULL, status, envir);
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
	}
	free_all_list(envir);
	return (0);
}

//void call_cmd(int status, char **pipe_split, t_env *envir)
//{
	/* code */
//}

//https://stackoverflow.com/questions/8389033/implementation-of-multiple-pipes-in-c
//http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html
//https://stackoverflow.com/questions/916900/having-trouble-with-fork-pipe-dup2-and-exec-in-c/



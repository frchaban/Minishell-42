/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/08 16:18:37 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_error(char *error, char *cmd)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
}

int main(int argc, char **argv, char **env)
{
	char ***cmd;
	int status;
	t_env *envir;
	int i;

	(void)argv;
	envp_to_list(&envir,env);
	if (argc != 1)
		return (0);
	status = 1;
	while (status)
	{
		i = -1;
		cmd = get_cmd();
		while (cmd[++i] != NULL)
		{
			if ( cmd[i] && cmd[i][0] != NULL)
				launch(cmd[i], &status, envir);
		}
		ft_free_3dim(cmd);
	}
	return (0);
}

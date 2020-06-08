/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/08 13:45:02 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char ***cmd;
	int status;
	t_env *envir;
	int i;

	(void)argv;
	(void)env;
	envir = NULL;
	if (argc != 1)
		return (0);
	status = 1;
	i = -1;
	while (status)
	{
		cmd = get_cmd();
		while (cmd[++i])
		{
			if (cmd[i][0] != NULL)
				launch(cmd[i], &status, envir);
		}
	}
	ft_free_3dim(cmd);
	return (0);
}

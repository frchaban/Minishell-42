/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/08 12:17:37 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	char **cmd;
	int status;

	if (argc != 1)
		return (0);
	status = 1;
	while (status)
	{
		cmd = get_cmd();
		if (cmd[0] != NULL)
		{
			launch(cmd, &status);
		}
		ft_free_2dim(cmd);
	}
	return (0);
}

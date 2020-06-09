/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:51:55 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/09 18:20:58 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(char **cmd)
{
	int i;
	int flag;
	t_list *args;
	int old_stdout;

	old_stdout = dup(STDOUT_FILENO);
	flag = 0;
	i = 0;
	if (ft_redir(cmd, 0) < 0)
		return ;
	args_to_list(&args, cmd);
	while (args)
	{
		ft_printf("%s\n", args->content);
		args = args->next;
	}
	free_args_list(args);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
}

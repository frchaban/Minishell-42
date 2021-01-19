/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_management_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:09:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 14:15:38 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_builtin(char *cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strchr(cmd, '='))
		return (1);
	else if (cmd[0] == '>')
		return (1);
	return (0);
}

void	launch_builtin(char *cmd, t_list *args, t_env *envir, int *status)
{
	if (ft_strcmp(cmd, "export") == 0)
		export_builtin(envir, args);
	else if (ft_strcmp(cmd, "echo") == 0)
		echo_builtin(args);
	else if (ft_strcmp(cmd, "cd") == 0)
		cd_builtin(args, envir);
	else if (ft_strcmp(cmd, "pwd") == 0)
		pwd_builtin(args, envir);
	else if (ft_strcmp(cmd, "unset") == 0)
		unset_builtin(args, envir);
	else if (ft_strcmp(cmd, "env") == 0)
		env_builtin(envir);
	else if (ft_strcmp(cmd, "exit") == 0)
		*status = exit_builtin(args, envir);
	else if (ft_strchr(cmd, '='))
		variable_update(cmd, args, envir);
}

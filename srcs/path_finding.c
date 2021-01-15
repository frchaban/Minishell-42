/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:25:31 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 10:21:13 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(t_env *envir)
{
	t_env *lst;

	lst = envir;
	while (lst)
	{
		if (ft_strequ(lst->key, "PATH") == 1)
			return (lst->content);
		else
			lst = lst->next;
	}
	return (NULL);
}

char	*ft_absolute_path(char *cmd, t_env *envir)
{
	char	*path;
	char	**path_folders;
	char	*test_path;
	int		i;
	int		fd;

	path = get_path(envir);
	(path == NULL || !path[0]) ? test_path = NULL : 0;
	path_folders = (path != NULL ? ft_split(path, ':') : NULL);
	i = -1;
	while (path_folders && path_folders[++i])
	{
		test_path = ft_strjoin(path_folders[i], "/");
		test_path = ft_strjoin_s1_freed(test_path, cmd);
		if ((fd = open(test_path, O_RDONLY)) == -1)
		{
			free(test_path);
			test_path = NULL;
		}
		else
			break ;
	}
	path_folders != NULL ? ft_free_2dim(path_folders) : 0;
	fd == 1 ? close(fd) : 0;
	return (test_path);
}

char	*get_absolute_path(char *cmd, t_env *envir)
{
	char	*absolute_path;
	int		save_errno;

	absolute_path = NULL;
	if (!cmd || !cmd[0])
		return (absolute_path);
	save_errno = errno;
	if (cmd[0] != '/' && ft_strncmp(cmd, "./", 2) != 0)
		absolute_path = ft_absolute_path(cmd, envir);
	if (absolute_path == NULL)
		absolute_path = ft_strdup(cmd);
	free(cmd);
	errno = save_errno;
	return (absolute_path);
}

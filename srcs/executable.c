#include "minishell.h"

char*	get_path(t_env *envir)
{
	t_env *lst;

	lst = envir;
	while (lst->next)
	{
		if (ft_strequ(lst->key, "PATH") == 1)
			return (lst->content);
		else
			lst = lst->next;
	}
	return (NULL);
}

char*	ft_absolute_path(char *cmd, t_env *envir)
{
	char *path;
	char **path_folders;
	char *test_path;
	int i;
	int fd;

	(path = get_path(envir)) == NULL ? test_path = NULL : 0;
	path_folders = (path != NULL ? ft_split(path, ':'): NULL);
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
			break;
	}
	path_folders != NULL ? ft_free_2dim(path_folders): 0;
	fd == 1 ? close(fd) : 0;
	return(test_path);
}

char	*get_absolute_path(char *cmd, t_env *envir)
{
	char *absolute_path;

	absolute_path = NULL;
	if (cmd[0] != '/' && ft_strncmp(cmd,"./", 2) != 0)
		absolute_path = ft_absolute_path(cmd, envir);
	if (absolute_path == NULL)
		absolute_path = ft_strdup(cmd);
	free(cmd);
	return (absolute_path);
}

void	execute(char **cmd, t_env *envir, int last_command)
{
	int		status;
	pid_t	pid;
	char	**env;

	pid = 0;
(void)last_command;
	status = 0;
	env = NULL;
	cmd[0] = get_absolute_path(cmd[0], envir);
	if (ft_strchr(cmd[0], '/') == 0 && ft_strncmp(cmd[0],"./", 2) != 0)
		return (ft_error("minishell: command not found: ", NULL ,cmd[0]));
	pid = fork();
	if (pid == -1)
		ft_printf("%s\n", strerror(errno)) ; // error to manage
	else if (pid == 0)  //enfant
	{
		env = list_to_envp(envir);
		ft_redir(cmd , 1);
		execve(cmd[0], cmd, env) == -1 ? ft_error("minishell: ", strerror(errno), cmd[0]) : 0;
		exit(1);
	}
	else if (pid > 0)  //parent
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
		exit(1);
	}
}

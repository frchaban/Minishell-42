#include "minishell.h"

int		is_absolute_path(char *cmd)
{
	if (cmd[0] == '/' || ft_strncmp(cmd,"./", 2) == 0)
		return (1);
	return (0);
}

/*void	absolute_path(char **cmd, t_list *envir)
{

}*/

void	execute(char **cmd)
{
	int		status;
	pid_t	pid;

	pid = 0;
	status = 0;

	pid = fork();
	if (pid == -1)
		ft_printf("%s\n", strerror(errno)) ; // error to manage
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			ft_printf("%s\n", strerror(errno)) ; // error to manage
		exit(EXIT_SUCCESS);
	}
}

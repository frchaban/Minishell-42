#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"


void 	pipe_cmd(char **cmd_split, int *previous_fd, int *status, t_env *envir)
{
	int		next_fd[2];
	pid_t	pid_fork;
	char	***cmd_semicolon;
	int		keep_fd[2];

	int		i[3];

	cmd_semicolon = parse_cmd(cmd_split[0]);
	if (previous_fd)
	{
		dup2(previous_fd[0], 0);
		close(previous_fd[0]);
	}
	if (cmd_split[1])
	{
		keep_fd[0] = dup(0);
		keep_fd[1] = dup(1);
		pipe(next_fd);	//add security
		pid_fork = fork();
		if (pid_fork == 0)  
		{
			close(next_fd[1]);
			pipe_cmd(cmd_split + 1, next_fd, status, envir);
			kill(pid_fork, 0);
			
		}
		else
		{
			close(next_fd[0]);
			dup2(next_fd[1], 1);
			close(next_fd[1]);
			//execvp(*cmd, cmd);
			launch(cmd_semicolon[0], status, envir);
			dup2(keep_fd[0], 0);
			close (keep_fd[0]);
			dup2(keep_fd[1], 1);
			close (keep_fd[0]);
		}
	}
	else
	{
		//execvp(*cmd, cmd);
		launch(cmd_split, status, envir);
	}
	close(previous_fd[0]);
}

int main(void)
{
	char *cmds[4];
	char **cmd;


	cmds[0] = "ls libft";
	cmds[2] = "grep a";
	cmds[1] = "sort";
	cmds[3] = NULL;


//	execvp(*cmd, cmd);
	pipe_cmd(cmds, NULL);
}


/*

void 	pipe_cmd(char **cmd, int *previous_fd)
{
	int		next_fd[2];
	pid_t	pid_fork;
	char	**cmd_split;
	

	cmd_split = ft_split(*cmd, ' ');
	if (previous_fd)
	{
		dup2(previous_fd[0], 0);
		close(previous_fd[0]);
		if (cmd[1])
		{
			pipe(next_fd);	//add security
			pid_fork = fork();
			if (pid_fork == 0)  
			{
				close(next_fd[1]);
				pipe_cmd(cmd + 1, next_fd);
			}
			else
			{
				close(next_fd[0]);
				dup2(next_fd[1], 1);
				close(next_fd[1]);
				execvp(*cmd_split, cmd_split);
			}
		}
		else
		{
			execvp(*cmd_split, cmd_split);
		}
		close(previous_fd[0]);
	}
	else
	{
		if (cmd[1])
		{
			pipe(next_fd);	//add security
			pid_fork = fork();
			if (pid_fork == 0)  
			{
				close(next_fd[1]);
				pipe_cmd(cmd + 1, next_fd);
			}
			else
			{
				close(next_fd[0]);
				dup2(next_fd[1], 1);
				close(next_fd[1]);
				execvp(*cmd_split, cmd_split);
			}
		}
		else
		{
			execvp(*cmd_split, cmd_split);
		}
	}
}
*/






































/*
int main(void)
{
	char *cmd[4];
	int i = 0;
	int fds[4];
	int fork_save;
	char **cmd_arg;
	char *line;

	cmd[0] = "ls libft";
	cmd[1] = "grep -v a";
	cmd[2] = "sort";
	cmd[3] = NULL;
	pipe(fds);
	fork_save = fork();

	if (fork_save == 0)
	{
		pipe(fds[2]);
		fork_save = fork();
		if (fork_save == 0)
		{
			close(fds[3]);
			close(0);
			dup2(fds[0], 0);
			cmd_arg = ft_split(cmd[1], ' ');
			execvp(cmd_arg[0], &cmd_arg[0]);
			ft_free_split(cmd_arg);
			close(fds[0]);
		}
		else
		{
			close(fds[1]);
			close(0);
			dup2(fds[0], 0);
			cmd_arg = ft_split(cmd[1], ' ');
			execvp(cmd_arg[0], &cmd_arg[0]);
			ft_free_split(cmd_arg);
			close(fds[0]);
		}
	}
	else
	{
		close(fds[0]);
		close(1);
		dup2(fds[1], 1);
		cmd_arg = ft_split(cmd[0], ' ');
		execvp(cmd_arg[0], &cmd_arg[0]);
		ft_free_split(cmd_arg);
		close(fds[1]);
	}

}
	
	// while (cmd[i])
	// {
	// 	if (cmd[i + 1])
	// 		pipe(new)
	// 	fork();
	// 	if (fork_save == 0)
	// 	{
	// 		if (i != 0)
	// 		{
	// 			dup2(fds[0], 0);
	// 			close(fds[0]);
	// 			close(fds[1]);
	// 		}
	// 		if (cmd[i + 1])
	// 		{	
	// 			close(fds[0]);
	// 			dup2(fds[1]), 1);
	// 			close(fds[1]);
	// 		}
	// 		cmd_arg = ft_split(cmd[i],' ');
	// 		execvp(cmd_arg[0], cmd_arg[1]);
	// 	}
	// 	else
	// 	{
	// 		if (i != 0)
	// 		{
	// 			close(fds[0]);
	// 			close(fds[1]);
	// 		}
			
	// 	}
		
	// }
*/

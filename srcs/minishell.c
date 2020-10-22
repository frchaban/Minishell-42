/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/10/22 15:50:11 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_error(char *cmd_n_error_msg, char *arg, int error_nb, t_env *env)
{
	if (env)
	{
		free(env->content);
		env->content = ft_itoa(error_nb);
	}
	if (cmd_n_error_msg)
		ft_putstr_fd(cmd_n_error_msg, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
}

void	not_builtin(char **cmd, t_env *envir, int pipe_c[3])
{
	pid_t	pid_fork;
	char	*line;
	char	*msg;

	
	pid_fork = fork();
	if (pid_fork == 0)
	{
		close(pipe_c[0]);
		execute(cmd, envir, 0);
		msg = ft_itoa(errno);
		puts(msg);
		write(pipe_c[1], msg, ft_strlen(msg));
		close(pipe_c[1]);
		exit(0);
	}
	else
	{
		close(pipe_c[1]);
		get_next_line(pipe_c[0], &line);
		close(pipe_c[0]);
		waitpid(pid_fork, &pipe_c[2], 0);
		if (ft_strlen(line) > 0)	
			envir->content = line;
		else if (WIFEXITED(pipe_c[2]))
    		envir->content = ft_itoa(WEXITSTATUS(pipe_c[2]));
		else if (WIFSIGNALED(pipe_c[2]))
    		envir->content = ft_itoa(WTERMSIG(pipe_c[2]));
	}
}

void	call_command(t_list *args, char **cmd, int *status, t_env *envir, int pipe_c[3])
{
	if (ft_strcmp(cmd[0], "export") == 0)
		export_builtin(envir, args);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		echo_builtin(args);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd_builtin(args, envir);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd_builtin(args, envir);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return unset_builtin(args, envir);
	else if (ft_strcmp(cmd[0], "env") == 0)
		env_builtin(envir);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		*status = exit_builtin();
	else if (ft_strchr(cmd[0], '='))
		variable_update(cmd[0], args, envir);
	else
		not_builtin(cmd, envir, pipe_c);

}

void	check_last_cmd(char **cmds, int *status, t_env *envir)
{
	int		i;
	char	**cmd;
	t_list	*args;
//	int		save_fdout;
//	int		save_fderr;
	int		pipe_c[3];

	i = 0;
	while (cmds[i + 1])
		i++;
	pipe(pipe_c);
	cmd = parse_cmd(&cmds[i]);
	if (ft_strequ(cmd[0], "grep") || ft_strequ(cmd[0], "cat"))
		return ;
	//save_fdout = dup(STDOUT_FILENO);
	//save_fderr = dup(STDERR_FILENO);
	//close(STDOUT_FILENO);
	//close(STDERR_FILENO);
	args = NULL;
	free(envir->content);
	envir->content = ft_itoa(0);
	if (cmd[1])
		args_to_list(&args, cmd);
	call_command(args, cmd, status, envir, pipe_c);
	free_args_list(args);
//	dup2(save_fdout, STDOUT_FILENO);
	//dup2(save_fderr, STDERR_FILENO);
	//close(save_fdout);
	//close(save_fderr);
}

void	main_2(int *status, char *line, t_env *envir)
{
	char	**semicolon_split;
	char	**cmd;
	int 	stt;
	int i;
	int		save_fdout;
	int		save_fderr;

	if (!line || !line[0])
		return ;
	semicolon_split = ft_split(line, ';');
	i = 0;
	
	while (semicolon_split[i])
	{
		save_fdout = dup(STDOUT_FILENO);
		save_fderr = dup(STDERR_FILENO);
		cmd = ft_split(semicolon_split[i++], '|');
		stt = 0;
		pipe_cmd(cmd, NULL, status, envir);
		//check_last_cmd(cmd, status, envir);
		ft_free_2dim(cmd);
		dup2(save_fdout, STDOUT_FILENO);
		dup2(save_fderr, STDERR_FILENO);
		close(save_fdout);
		close(save_fderr);
	}
	
	ft_free_2dim(semicolon_split);
}

int		check_cat_ctrl_c_case(char *line)
{
	char *cp;
	char **cp2;

	if (!(cp = malloc(sizeof(*cp) * (ft_strlen(line) + 1))))
		return (-1);
	ft_strcpy(cp, line);
	cp = ft_strtrim_freed(cp, " \t");
	if (!cp || !cp[0])
		return (1);
	cp2 = ft_split(cp, ' ');
	free(cp);
	if ((ft_strequ(cp2[0], "cat") == 1 && !cp2[1]) || ft_strequ(cp2[0], "grep") == 1)
	{
		ft_free_2dim(cp2);
		return (0);
	}
	ft_free_2dim(cp2);
	return (1);
}

void	clean_line_from_empty_quote(char *line)
{
	int		i;
	int		save_index;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			save_index = i++;
			while (ft_is_whitespaces(line[i]))
				i++;
			if (line[save_index] == line[i])
			{
				ft_strcpy(&line[save_index + 1], &line[i]);
				i = save_index + 1;
			}
		}
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	int	status;
	t_env	*envir;
	int	print_prompt;

	(void)argv;
	print_prompt = 1;
	if (argc != 1)
		return (0);
	envp_to_list(&envir, env);
	remove_ctrl("stty", " -echoctl", envir);
	status = 1;
	while (status)
	{
		line = get_cmd(print_prompt);
		clean_line_from_empty_quote(line);
		clean_useless_quote(line);
		clean_useless_simple_quote(line);
		print_prompt = check_cat_ctrl_c_case(line);
		main_2(&status, line, envir);
		free(line);
	}
	free_all_list(envir);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/10/19 13:44:23 by gdupont          ###   ########.fr       */
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
		execute(cmd, envir);
		msg = ft_itoa(errno);
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
	int		save_fdout;
	int		save_fderr;
	int		pipe_c[3];

	i = 0;
	while (cmds[i + 1])
		i++;
	pipe(pipe_c);
	cmd = parse_cmd(&cmds[i]);
	save_fdout = dup(STDOUT_FILENO);
	save_fderr = dup(STDERR_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	args = NULL;
	free(envir->content);
	envir->content = ft_itoa(0);
	if (cmd[1])
		args_to_list(&args, cmd);
	call_command(args, cmd, status, envir, pipe_c);
	free_args_list(args);
	dup2(save_fdout, STDOUT_FILENO);
	dup2(save_fderr, STDERR_FILENO);
	close(save_fdout);
	close(save_fderr);
}

void	main_2(int *status, char *line, t_env *envir)
{
	char	**semicolon_split;
	char	**cmd;
	pid_t	pid;
	int 	stt;
	int i;

	if (!line || !line[0])
		return ;
	semicolon_split = ft_split(line, ';');
	i = 0;
	while (semicolon_split[i])
	{
		cmd = ft_split(semicolon_split[i++], '|');
		pid = fork();
		stt = 0;
		if (pid == 0)
		{
			pipe_cmd(cmd, NULL, status, envir);
			exit(1);
		}
		else
			waitpid(pid, &stt, 0);
		check_last_cmd(cmd, status, envir);
		ft_free_2dim(cmd);
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
	//remove_ctrl("stty", " -echoctl", envir);
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




void	write_errno(int fd)
{
	if (errno == EPERM ) 
		write(fd, "1", 1);
	else if (errno == ENOENT) 
		write(fd, "2", 1);
	else if (errno == ESRCH ) 
		write(fd, "3", 1);
	else if (errno == EINTR ) 
		write(fd, "4", 1);
	else if (errno == EIO   ) 
		write(fd, "5", 1);
	else if (errno == ENXIO ) 
		write(fd, "6", 1);
	else if (errno == E2BIG ) 
		write(fd, "7", 1);
	else if (errno == ENOEXEC) 
		write(fd, "8", 1);
	else if (errno == EBADF ) 
		write(fd, "9", 1);
	else if (errno == ECHILD) 
		write(fd, "10", 2);
	else if (errno == EDEADLK) 
		write(fd, "11", 2);
	else if (errno == ENOMEM) 
		write(fd, "12", 2);
	else if (errno == EACCES) 
		write(fd, "13", 2);
	else if (errno == EFAULT) 
		write(fd, "14", 2);
	else if (errno == ENOTBLK) 
		write(fd, "15", 2);
	else if (errno == EBUSY ) 
		write(fd, "16", 2);
	else if (errno == EEXIST) 
		write(fd, "17", 2);
	else if (errno == EXDEV ) 
		write(fd, "18", 2);
	else if (errno == ENODEV) 
		write(fd, "19", 2);
	else if (errno == ENOTDIR) 
		write(fd, "20", 2);
	else if (errno == EISDIR) 
		write(fd, "21", 2);
	else if (errno == EINVAL) 
		write(fd, "22", 2);
	else if (errno == ENFILE) 
		write(fd, "23", 2);
	else if (errno == EMFILE) 
		write(fd, "24", 2);
	else if (errno == ENOTTY) 
		write(fd, "25", 2);
	else if (errno == ETXTBSY) 
		write(fd, "26", 2);
	else if (errno == EFBIG ) 
		write(fd, "27", 2);
	else if (errno == ENOSPC) 
		write(fd, "28", 2);
	else if (errno == ESPIPE) 
		write(fd, "29", 2);
	else if (errno == EROFS ) 
		write(fd, "30", 2);
	else if (errno == EMLINK) 
		write(fd, "31", 2);
	else if (errno == EPIPE) 
		write(fd, "32", 2);
	else if (errno == EDOM) 
		write(fd, "33", 2);
	else if (errno == ERANGE) 
		write(fd, "34", 2);
	else if (errno == EAGAIN) 
		write(fd, "35", 2);
	else if (errno == EWOULDBLOCK) 
		write(fd, "35", 2); 
	else if (errno == EINPROGRESS) 
		write(fd, "36", 2);
	else if (errno == EALREADY) 
		write(fd, "37", 2);
	else if (errno == ENOTSOCK) 
		write(fd, "38", 2);
	else if (errno == EDESTADDRREQ) 
		write(fd, "39", 2);
	else if (errno == EMSGSIZE) 
		write(fd, "40", 2);
	else if (errno == EPROTOTYPE) 
		write(fd, "41", 2);
	else if (errno == ENOPROTOOPT) 
		write(fd, "42", 2);
	else if (errno == EPROTONOSUPPORT)
		write(fd, "43", 2);
	else if (errno == ESOCKTNOSUPPORT)
		write(fd, "44", 2);
	else if (errno == ENOTSUP) 
		write(fd, "45", 2);
	else if (errno == EOPNOTSUPP) 
		write(fd, "45", 2);
	else if (errno == EPFNOSUPPORT) 
		write(fd, "46", 2);
	else if (errno == EAFNOSUPPORT) 
		write(fd, "47", 2);
	else if (errno == EADDRINUSE) 
		write(fd, "48", 2);
	else if (errno == EADDRNOTAVAIL) 
		write(fd, "49", 2);
	else if (errno == ENETDOWN) 
		write(fd, "50", 2);
	else if (errno == ENETUNREACH) 
		write(fd, "51", 2);
	else if (errno == ENETRESET) 
		write(fd, "52", 2);
	else if (errno == ECONNABORTED) 
		write(fd, "53", 2);
	else if (errno == ECONNRESET) 
		write(fd, "54", 2);
	else if (errno == ENOBUFS) 
		write(fd, "55", 2);
	else if (errno == EISCONN) 
		write(fd, "56", 2);
	else if (errno == ENOTCONN) 
		write(fd, "57", 2);
	else if (errno == ESHUTDOWN) 
		write(fd, "58", 2);
	else if (errno == ETOOMANYREFS) 
		write(fd, "59", 2);
	else if (errno == ETIMEDOUT) 
		write(fd, "60", 2);
	else if (errno == ECONNREFUSED) 
		write(fd, "61", 2);
	else if (errno == ELOOP ) 
		write(fd, "62", 2);
	else if (errno == ENAMETOOLONG) 
		write(fd, "63", 2);
	else if (errno == EHOSTDOWN) 
		write(fd, "64", 2);
	else if (errno == EHOSTUNREACH) 
		write(fd, "65", 2);
	else if (errno == ENOTEMPTY) 
		write(fd, "66", 2);
	else if (errno == EPROCLIM) 
		write(fd, "67", 2);
	else if (errno == EUSERS) 
		write(fd, "68", 2);
	else if (errno == EDQUOT) 
		write(fd, "69", 2);
	else if (errno == ESTALE) 
		write(fd, "70", 2);
	else if (errno == EREMOTE) 
		write(fd, "71", 2);
	else if (errno == EBADRPC) 
		write(fd, "72", 2);
	else if (errno == ERPCMISMATCH) 
		write(fd, "73", 2);
	else if (errno == EPROGUNAVAIL) 
		write(fd, "74", 2);
	else if (errno == EPROGMISMATCH) 
		write(fd, "75", 2);
	else if (errno == EPROCUNAVAIL) 
		write(fd, "76", 2);
	else if (errno == ENOLCK) 
		write(fd, "77", 2);
	else if (errno == ENOSYS) 
		write(fd, "78", 2);
	else if (errno == EFTYPE) 
		write(fd, "79", 2);
	else if (errno == EAUTH ) 
		write(fd, "80", 2);
	else if (errno == ENEEDAUTH) 
		write(fd, "81", 2);
	else if (errno == EPWROFF) 
		write(fd, "82", 2);     
	else if (errno == EDEVERR) 
		write(fd, "83", 2);     
	else if (errno == EOVERFLOW) 
		write(fd, "84", 2);
	else if (errno == EBADEXEC) 
		write(fd, "85", 2);
	else if (errno == EBADARCH)
		write(fd, "86", 2);
	else if (errno == ESHLIBVERS)
		write(fd, "87", 2); 
	else if (errno == EBADMACHO)
		write(fd, "88", 2);
	else if (errno == ECANCELED)
		write(fd, "89", 2);
	else if (errno == EIDRM )
		write(fd, "90", 2);
	else if (errno == ENOMSG)
		write(fd, "91", 2);
	else if (errno == EILSEQ)
		write(fd, "92", 2);
	else if (errno == ENOATTR)
		write(fd, "93", 2);
	else if (errno == EBADMSG)
		write(fd, "94", 2);
	else if (errno == EMULTIHOP)
		write(fd, "95", 2);
	else if (errno == ENODATA)
		write(fd, "96", 2);
	else if (errno == ENOLINK)
		write(fd, "97", 2);
	else if (errno == ENOSR )
		write(fd, "98", 2);
	else if (errno == ENOSTR)
		write(fd, "99", 2);
	else if (errno == EPROTO) 
		write(fd, "100", 3);
	else if (errno == ETIME) 
		write(fd, "101", 3); 
	else if (errno == EOPNOTSUPP)
		write(fd, "102", 3);
	else if (errno == ENOPOLICY)
		write(fd, "103", 3);
	else if (errno == ENOTRECOVERABLE)
		write(fd, "104", 3);
	else if (errno == EOWNERDEAD)
		write(fd, "105", 3);
	else if (errno == EQFULL)
		write(fd, "106", 3);
	else if (errno == ELAST)
		write(fd, "106", 3);
}


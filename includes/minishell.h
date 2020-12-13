/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:32:44 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/13 16:55:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/errno.h>
# include <errno.h>
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/libftprintf.h"

# define NOT_EXPORT 0
# define EXPORT 1
int G_PRINT_PROMPT;

typedef struct		s_env
{
	char			*key;
	char			*content;
	int				exportable;
	struct s_env	*next;
}					t_env;

char				*get_cmd(void);
void				execute(char **cmd, t_env *envir);
void				launch(char **cmd, int *status, t_env *envir);
char				**parse_cmd(char **line);

void				cd_builtin(t_list *args, t_env *envir);
void				pwd_builtin(t_list *args, t_env *env);
void				echo_builtin(t_list *args);
int					exit_builtin(void);
void				export_builtin(t_env *envir, t_list *args);
void				env_builtin(t_env *envir);
void				unset_builtin(t_list *args, t_env *envir);

void				variable_update(char *first_cmd,
										t_list *args, t_env *envir);

void				ft_error(char *cmd_n_error_msg, char *arg,
								int err_nb, t_env *env);
char				**list_to_envp(t_env *envir);

int					envp_to_list(t_env **envir, char **envp);
t_env				*set_up_elem(char *line, int exportable);
t_env				*ft_last_elem(t_env *envir);
void				free_elem_list(t_env *env);
void				free_all_list(t_env *envir);
char				*get_var_content(char *cmd, t_env *envir);
int					ft_redir(char **cmd, int flag);

int					args_to_list(t_list **args, char **cmd);
char				**list_to_arg(t_list *args, char *cmd);
void				free_args_list(t_list *args);
int					args_size(t_list *args);

char				**ft_parse_cmd(char *cmd);

void				signal_ctrl_c();
void				signal_ctrl_back_exit();
void				signal_ctrl_back_nothing();
void				remove_ctrl(char *arg1, char *arg2, t_env *envir);
char				*get_absolute_path(char *cmd, t_env *envir);

void				pipe_cmd(char **cmd_split, int *p_fd,
								int *status, t_env *envir);

void				export_print_lst(t_env *envir);
void				clean_useless_simple_quote(char *cmd);
void				clean_useless_quote(char *cmd);

int					is_builtin(char *cmd);
void				launch_builtin(char *cmd, t_list *args,
									t_env *envir, int *status);
char				*get_absolute_path(char *cmd, t_env *envir);
char				*ft_absolute_path(char *cmd, t_env *envir);
char				*get_path(t_env *envir);

#endif

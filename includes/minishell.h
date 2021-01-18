/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:32:44 by frchaban          #+#    #+#             */
/*   Updated: 2021/01/18 20:33:38 by gdupont          ###   ########.fr       */
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

int g_print_prompt;
int	g_ctrl_backslash;
int	g_ctrl_c;
int g_redirections;

typedef struct		s_env
{
	char			*key;
	char			*content;
	int				exportable;
	struct s_env	*next;
}					t_env;

/*
** PARSE
*/

char				*get_cmd(void);
char				**parse_cmd(char **line, t_env *env);
char				**handle_inside_quote_split(char *line, char c);
char				**put_back_character(char *line, char c);
int					check_valid_quote_nb(char *cmd);
char				*update_line(char *line, int i, t_env *envir);
void				update_quote_2(char *line, int i);
void				ft_update_quote(char *line);
char				*ft_update_variable(char *line, t_env *envir);
void				variable_update(char *first_cmd,
										t_list *args, t_env *envir);
int					pass_whitespaces(char *line, int i);
char				**ft_parse_cmd(char *cmd);
int					word_end(int i, char *cmd, char *end_next_word);
int					is_escaped(char *cmd, int i);
void				handle_quote(char *cmd);
void				handle_backslash_and_begin_quote(char *cmd);
void				update_cmd(char **cmd, int i, int flag);
char				*get_var_content(char *cmd, t_env *envir);
int					ft_redir(char **cmd, int flag);
int					handle_min_sup(char **cmd, int i, int flag);
void				check_double_semicolon(char *line, t_env *envir);
void				check_hashtag(char *line);
int					ft_count_word(char *cmd);
int					go_to_end_word(int i, char *cmd);
char				**devide_cmd(char *cmd);

/*
** ERROR & SIGNAL
*/

void				ft_error(char *cmd_n_error_msg, char *arg,
								int err_nb, t_env *env);
void				signal_ctrl_c(int signal);
void				ft_sigquit(int sig);
void				signal_ctrl_back_nothing(int signal);
void				remove_ctrl(char *arg1, char *arg2, t_env *envir);
void				adjust_errno_sigquit(t_env *envir);

/*
** EXECUTE & LAUNCH CMDS
*/

void				execute(char **cmd, t_env *envir);
void				launch(char **cmd, int *status, t_env *envir);
char				*get_absolute_path(char *cmd, t_env *envir);
char				*ft_absolute_path(char *cmd, t_env *envir);
char				*get_path(t_env *envir);
int					is_builtin(char *cmd);
void				launch_builtin(char *cmd, t_list *args,
									t_env *envir, int *status);
char				*get_absolute_path(char *cmd, t_env *envir);
void				pipe_cmd(char **cmd_split, int *p_fd,
								int *status, t_env *envir);

/*
** BUILTIN
*/

void				cd_builtin(t_list *args, t_env *envir);
void				pwd_builtin(t_list *args, t_env *env);
void				echo_builtin(t_list *args);
int					exit_builtin(t_list *args, t_env *env);
void				export_builtin(t_env *envir, t_list *args);
void				export_print_lst(t_env *envir);
void				env_builtin(t_env *envir);
void				unset_builtin(t_list *args, t_env *envir);

/*
** LINKED LIST TOOLS
*/

char				**list_to_envp(t_env *envir);
int					envp_to_list(t_env **envir, char **envp);
t_env				*set_up_elem(char *line, int exportable);
t_env				*ft_last_elem(t_env *envir);
void				free_elem_list(t_env *env);
void				free_all_list(t_env *envir);
void				args_to_list(t_list **args, char **cmd);
char				**list_to_arg(t_list *args, char *cmd);
void				free_args_list(t_list *args);
int					args_size(t_list *args);

#endif

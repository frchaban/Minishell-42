/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:32:44 by frchaban          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/06/10 15:12:43 by frchaban         ###   ########.fr       */
=======
/*   Updated: 2020/06/10 10:58:31 by gdupont          ###   ########.fr       */
>>>>>>> e7868337867e4cc6179f72aad5717a20f9995938
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
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/libftprintf.h"

# define NOT_EXPORT 0
# define EXPORT 1

typedef struct 		s_env
{
	char 			*key;
	char 			*content;
	int				exportable;
	struct s_env 	*next;
}					t_env;

char		***get_cmd(void);
void		execute(char **cmd, t_env *envir);
void		launch(char **cmd, int *status, t_env *envir);

void		cd_builtin(t_list *args, t_env *envir);
void		pwd_builtin(t_list *args);
void		echo_builtin(t_list *args);
int			exit_builtin(void);
void		export_builtin(t_env *envir, t_list *args);
void  		env_builtin(t_env *envir);

void		ft_error(char *error, char *error_errno, char *cmd);
char  		**list_to_envp(t_env *envir);

int			envp_to_list(t_env **envir, char **envp);
t_env		*set_up_elem(char *line, int exportable);
t_env		*ft_last_elem(t_env *envir);
void		free_all_list(t_env *envir);
char		*get_var_content(char *cmd, t_env *envir);
int			ft_redir(char **cmd, int flag);

int			args_to_list(t_list **args, char **cmd);
void		free_args_list(t_list *args);
int			args_size(t_list  *args);

char		 **ft_parse_cmd(char *cmd);


#endif

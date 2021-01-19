# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 11:29:54 by frchaban          #+#    #+#              #
#    Updated: 2021/01/19 14:38:43 by gdupont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

PATH_SRCS = srcs

SRCS_LIST		= \
					minishell.c \
					cmd_management.c \
					cmd_management_2.c \
					executable.c \
					echo_builtin.c \
					env_builtin.c \
					unset_builtin.c \
					export_builtin.c \
					args_lst_manage.c \
					args_lst_manage_2.c \
					cd_builtin.c \
					pwd_builtin.c \
					lst_manage.c \
					lst_manage_2.c \
					redirections.c \
					redirections_2.c \
					parse.c \
					parse_2.c \
					parse_3.c \
					parse_tools.c \
					parse_tools2.c \
					variable_update.c \
					signal_handler.c \
					exit_builtin.c \
					pipe_management.c \
					error.c \
					path_finding.c


SRCS = $(addprefix ${PATH_SRCS}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes

LIBFT = libft

LFLAGS	= -L $(LIBFT) -lft

SGFLAGS = -g ulimit -c unlimited

FFLAGS = -g3 -fsanitize=address

$(NAME) :	$(OBJS) 
	@make -C $(LIBFT)
	$(CC) $(FLAGS) $(LFLAGS) $(FFLAGS) $(INCLUDES) $(OBJS) libft/libft.a -o $(NAME) 

all : $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(FFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus

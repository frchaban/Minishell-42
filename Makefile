# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 11:29:54 by frchaban          #+#    #+#              #
#    Updated: 2020/10/23 10:57:55 by gdupont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

PATH_SRCS = srcs

SRCS_LIST		= \
					minishell.c \
					cmd_management.c \
					executable.c \
					echo_builtin.c \
					env_builtin.c \
					unset_builtin.c \
					export_builtin.c \
					args_lst_manage.c \
					cd_builtin.c \
					pwd_builtin.c \
					lst_manage.c \
					lst_manage_2.c \
					redirections.c \
					parse.c \
					variable_update.c \
					signal_handler.c \
					exit_builtin.c \
					pipe_management.c


SRCS = $(addprefix ${PATH_SRCS}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes

LIBFT = libft

LFLAGS	= -L $(LIBFT) -lft

SGFLAGS = -g ulimit -c unlimited

FFLAGS = -g3 -fsanitize=address

all :	$(NAME)

$(NAME) :	$(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(FLAGS) $(LFLAGS) $(FFLAGS) $(INCLUDES) $(OBJS) libft/libft.a -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(FFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(LIBFT)

fclean: clean
	@rm -f  $(NAME)
	@make fclean -s -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus

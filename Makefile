# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 11:29:54 by frchaban          #+#    #+#              #
#    Updated: 2020/05/25 14:59:53 by frchaban         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

PATH_SRCS = srcs

SRCS_LIST		= \
					minishell.c \
					echo_builtin.c


SRCS = $(addprefix ${PATH_SRCS}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes

LIBFT = libft

LFLAGS	= -L $(LIBFT) -lft

SGFLAGS = -g -fsanitize=address

all :	$(NAME)

$(NAME) :	$(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(SGFLAGS) $(FLAGS) $(LFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(LIBFT)

fclean: clean
	@rm -f  $(NAME)
	@make fclean -s -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus

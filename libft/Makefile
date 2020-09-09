# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/03 18:24:04 by frchaban          #+#    #+#              #
#    Updated: 2020/07/29 15:54:55 by gdupont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

PATH_SRCS = ./srcs

SRCS_LIST = \
				libft/ft_atof.c \
				libft/ft_atoi.c \
				libft/ft_atoi_freed.c \
				libft/ft_bzero.c \
				libft/ft_calloc.c \
				libft/ft_free2dim.c \
				libft/ft_free3dim.c \
				libft/ft_isalnum.c \
				libft/ft_isalpha.c \
				libft/ft_isascii.c \
				libft/ft_isdigit.c \
				libft/ft_isprint.c \
				libft/ft_itoa.c \
				libft/ft_itoa_long.c \
				libft/ft_len_int.c \
				libft/ft_lhex.c \
				libft/ft_lstadd_back.c \
				libft/ft_lstadd_front.c \
				libft/ft_lstclear.c \
				libft/ft_lstdelone.c \
				libft/ft_lstiter.c \
				libft/ft_lstlast.c \
				libft/ft_lstmap.c \
				libft/ft_lstnew.c \
				libft/ft_lstsize.c \
				libft/ft_memalloc.c \
				libft/ft_memccpy.c \
				libft/ft_memchr.c \
				libft/ft_memcmp.c \
				libft/ft_memcpy.c \
				libft/ft_memdel.c \
				libft/ft_memmove.c \
				libft/ft_memset.c \
				libft/ft_putchar.c \
				libft/ft_putchar_fd.c \
				libft/ft_putendl.c \
				libft/ft_putendl_fd.c \
				libft/ft_putnbr.c \
				libft/ft_putnbr_fd.c \
				libft/ft_putstr.c \
				libft/ft_putstr_fd.c \
				libft/ft_split.c \
				libft/ft_split_freed.c \
				libft/ft_strcat.c \
				libft/ft_strchr.c \
				libft/ft_strclr.c \
				libft/ft_strcmp.c \
				libft/ft_strcpy.c \
				libft/ft_strdel.c \
				libft/ft_strdup.c \
				libft/ft_strequ.c \
				libft/ft_striter.c \
				libft/ft_striteri.c \
				libft/ft_strjoin.c \
				libft/ft_strjoin_freed.c \
				libft/ft_strjoin_s1_freed.c \
				libft/ft_strlcat.c \
				libft/ft_strlcpy.c \
				libft/ft_strlen.c \
				libft/ft_strmap.c \
				libft/ft_strmapi.c \
				libft/ft_strncat.c \
				libft/ft_strncmp.c \
				libft/ft_strncpy.c \
				libft/ft_strnequ.c \
				libft/ft_strnew.c \
				libft/ft_strnstr.c \
				libft/ft_strrchr.c \
				libft/ft_strstr.c \
				libft/ft_strtrim.c \
				libft/ft_strtrim_freed.c \
				libft/ft_substr.c \
				libft/ft_tolower.c \
				libft/ft_count_split.c\
				libft/ft_toupper.c \
				libft/ft_uhex.c \
				libft/ft_sort_strings.c \
				libft/ft_print_split.c \
				printf/ft_conv.c \
				printf/ft_display.c \
				printf/ft_display_tools.c \
				printf/ft_parsing.c \
				printf/ft_parsing_tools.c \
				printf/ft_printf.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c

SRCS = $(addprefix ${PATH_SRCS}/, ${SRCS_LIST})

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes

all:	 $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $^

%.o: %.c
	$(CC) $(FLAGS) -c $< $(INCLUDES) -o $@

clean:
			rm -f $(OBJS)

fclean: clean
			rm -f  $(NAME)

re: fclean all

.PHONY: all clean fclean re

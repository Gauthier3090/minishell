# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldavids <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 14:03:18 by ldavids           #+#    #+#              #
#    Updated: 2019/11/05 13:51:54 by ldavids          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE = ./libft.h

PATH_SRC = ./

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_putnbr_fd.c ft_strtrim.c ft_atoi.c ft_putstr_fd.c ft_substr.c\
	   ft_bzero.c ft_split.c ft_tolower.c ft_calloc.c\
	   ft_strchr.c ft_toupper.c ft_isalnum.c\
	   ft_strdup.c ft_isalpha.c ft_memccpy.c\
	   ft_strjoin.c ft_isascii.c ft_memchr.c ft_strlcat.c ft_isdigit.c\
	   ft_memcmp.c ft_strlcpy.c ft_isprint.c ft_memcpy.c ft_strlen.c\
	   ft_itoa.c ft_memmove.c ft_strmapi.c ft_memset.c ft_strncmp.c\
	   ft_putchar_fd.c ft_strnstr.c ft_putendl_fd.c ft_strrchr.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
	   	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c ft_lstiter_bonus.c

BONUSOBJ = $(BONUS:.c=.o)

OBJ = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	    ar rc $(NAME) $(OBJ)

bonus: $(BONUSOBJ) $(INCLUDE)
		ar rc $(NAME) $(BONUSOBJ)

clean:
	    /bin/rm -f $(OBJ) $(BONUSOBJ)
fclean: clean
	    /bin/rm -f $(NAME)
re:	fclean all

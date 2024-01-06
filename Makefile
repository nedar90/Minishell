# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 11:35:01 by nrajabia          #+#    #+#              #
#    Updated: 2023/08/26 09:17:21 by nrajabia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		:= minishell
CC			:= gcc
CFLAGS		:= -Wextra -Wall -Werror -g3
RFLAGS		:= -lreadline -lhistory

HEADERS		:= -I ./includes
SRCS		:=  $(shell find ./src -iname "*.c")\
					$(shell find ./libft -iname "*.c")
OBJS		:= ${SRCS:.c=.o}

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(RFLAGS) -o $(NAME)

all: $(NAME)


clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
#&& printf "Compiling: $(notdir $<)\ "

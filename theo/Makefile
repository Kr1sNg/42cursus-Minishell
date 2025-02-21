# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:04:41 by tbahin            #+#    #+#              #
#    Updated: 2025/02/21 01:24:22 by tbahin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDE = ./includes/

CC = cc
CFLAG = -Wall -Wextra -Werror -g

SRCS =./srcs/buildins.c ./srcs/main.c

OBJS = ${SRCS:.c=.o}

all : ${NAME} 

${NAME} : $(OBJS)
	make bonus -C ./libft
	$(CC) $(CFLAG) -o $(NAME) $(OBJS) -L./libft -lft

bonus: $(OBJSB)
	make bonus -C ./libft
	$(CC) $(CFLAG) -o $(NAME) $(OBJS) -L./libft -lft

%.o: %.c
	$(CC) $(CFLAG) -I $(INCLUDE) -c $< -o $@

clean :
	rm -f ${OBJS}
	make clean -C ./libft

fclean : clean
	rm -f ${NAME}
	make fclean -C ./libft

re : fclean all

.phony : all clean fclean re bonus

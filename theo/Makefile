# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:04:41 by tbahin            #+#    #+#              #
#    Updated: 2025/02/22 21:15:43 by tbahin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDE = ./includes/

CC = cc
CFLAG = -Wall -Wextra -Werror -g

SRCS =./srcs/buildins.c ./srcs/main.c ./srcs/export_cmd/cmd_export.c \
./srcs/export_cmd/cmd_export_no_args.c ./srcs/export_cmd/cmd_export_args.c \
./srcs/unset_cmd/cmd_unset.c

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

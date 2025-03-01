# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:04:41 by tbahin            #+#    #+#              #
#    Updated: 2025/03/01 20:35:00 by tbahin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDE = ./includes/

CC = cc
CFLAG = -Wall -Wextra -Werror

SRCS =./src/main.c ./src/errors/error_input.c ./src/executing/execute_main.c ./src/lexing/lexing.c ./src/lexing/lexing_split_token.c \
./src/lexing/tokenize.c ./src/parsing/parsing_ast_utils.c ./src/parsing/parsing_free.c ./src/parsing/parsing_main.c ./src/parsing/parsing_support.c \
./src/parsing/test_parsing.c ./src/parsing/parsing_create_ast.c ./src/signal/signal_hander.c ./src/buildins/buildins.c \
./src/buildins/export_cmd/cmd_export.c ./src/buildins/export_cmd/cmd_export_no_args.c ./src/buildins/export_cmd/cmd_export_args.c \
./src/buildins/unset_cmd/cmd_unset.c ./src/buildins/cd_cmd.c ./src/buildins/cmd_check/exec_cmd.c ./src/buildins/cmd_check/multi_pipe.c\
./src/buildins/cmd_check/outils.c ./src/buildins/cmd_check/parsing.c ./src/buildins/cmd_check/check_valide_cmd.c \

OBJS = ${SRCS:.c=.o}

all : ${NAME} 

${NAME} : $(OBJS)
	make -C ./libft
	$(CC) ${CFLAGS} -o $(NAME) $(OBJS) -L./libft -lft -lreadline

%.o: %.c
	$(CC) ${CFLAGS} -I $(INCLUDE) -c $< -o $@

clean :
	rm -f ${OBJS}
	make clean -C ./libft

fclean : clean
	rm -f ${NAME}
	make fclean -C ./libft

re : fclean all

.phony : all clean fclean re bonus

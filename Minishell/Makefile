# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:04:41 by tbahin            #+#    #+#              #
#    Updated: 2025/03/03 21:53:59 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

# Libft
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Source Files
DIR_SRCS	= src
SUBDIRS		= main buildins cmd_check errors executing export_cmd lexing \
				parsing redirect signal unset_cmd 
SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_SRCS)/, $(dir)))
SRCS		= $(foreach dir, $(SRCS_DIRS), $(wildcard $(dir)/*.c))

# Object Files
OBJS		= $(SRCS:.c=.o)

# Include and Flags
INCLUDE		= -Iinclude
LDFLAGS     = -L/opt/homebrew/opt/readline/lib -lreadline
CFLAGS		= -Wall -Wextra -Werror
CC			= cc -I/opt/homebrew/opt/readline/include
RM			= rm -rf

# Target
all : $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS)

# Clean
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean:	clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

bonus: re

.PHONY : all clean fclean re bonus

NAME = libft.a
INCLUDE_DIR = .
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = ft_isprint.c ft_putendl_fd.c ft_strlcat.c\
ft_substr.c ft_atoi.c ft_itoa.c ft_putnbr_fd.c\
ft_strlcpy.c ft_tolower.c ft_bzero.c ft_memchr.c\
ft_putstr_fd.c ft_strlen.c ft_toupper.c ft_calloc.c\
ft_memcmp.c ft_split.c ft_strmapi.c ft_isalnum.c\
ft_memcpy.c ft_strchr.c ft_strcmp.c ft_isalpha.c\
ft_memmove.c ft_strdup.c ft_strnstr.c ft_isascii.c\
ft_memset.c ft_striteri.c ft_strrchr.c ft_isdigit.c\
ft_putchar_fd.c ft_strjoin.c ft_strtrim.c\
ft_cprints.c ft_iprints.c ft_lowxprints.c\
ft_pprints.c ft_printf.c ft_sprints.c ft_uprints.c ft_upxprints.c\
ft_putchar_fd.c ft_putstr_fd.c ft_itoa.c ft_strlen.c\
get_next_line.c get_next_line_utils.c ft_strncmp.c\
ft_strlen_n.c ft_strcpy.c ft_strlen_egal.c

BONUS = ft_lstnew.c ft_lstadd_front.c\
ft_lstsize.c ft_lstlast.c\
ft_lstadd_back.c ft_lstdelone.c\
ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)
OBJSB = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJSB)
	ar rcs $(NAME) $(OBJS) $(OBJSB)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

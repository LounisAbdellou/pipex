CC = cc
NAME = pipex
INCLUDES = ./includes/
CFLAGS = -Wall -Wextra -Werror -I ./includes
LIBFT = ./libft/libft.a

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	${CC} $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

clean:
	@make clean -C libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

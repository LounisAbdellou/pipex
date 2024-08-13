CC = cc
NAME = pipex
INCLUDES = ./includes/
CFLAGS = -Wall -Wextra -Werror -I ./includes
LIBFT = ./libft/libft.a

SRCS = srcs/main.c srcs/utils.c

OBJS = $(SRCS:.c=.o)

SRCS_BONUS = bonus/main_bonus.c bonus/utils_bonus.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

clean:
	@make clean -C libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) $(LIBFT)

.PHONY: all clean fclean re bonus

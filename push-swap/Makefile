################################################

NAME = push_swap

SRCS = push_swap.c main.c
OBJS = $(SRCS:.c=.o)

CC = clang
#CFLAGS = -Wall -Wextra -Werror -g # -g per debug gdb
CFLAGS = -Wall -Wextra -Werror -g -Ift_printf/libft


LIBFT_DIR = ft_printf
LIBFT = $(LIBFT_DIR)/libftprintf.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lftprintf

FT_DIR = ft_printf/libft
FT = $(FT_DIR)/libft.a
FT_FLAGS = -L$(FT_DIR) -lft

#MLX_DIR = minilibx-linux
#MLX = $(MLX_DIR)/libmlx_linux.a
#MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm



all: $(NAME)

$(NAME): $(LIBFT) $(FT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(FT_FLAGS) -o $(NAME)

$(FT):
	$(MAKE) -C $(FT_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(FT_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
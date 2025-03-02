################################################

NAME = fractol

SRCS = fractol.c fractals.c main.c
OBJS = $(SRCS:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -g # -g per debug gdb

LIBFT_DIR = ft_printf
LIBFT = $(LIBFT_DIR)/libftprintf.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lftprintf

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

FT_DIR = ft_printf/libft
FT = $(FT_DIR)/libft.a
FT_FLAGS = -L$(FT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) $(FT_FLAGS) -o $(NAME)

$(FT):
	$(MAKE) -C $(FT_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(FT_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
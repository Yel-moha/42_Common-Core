NAME		= fractol

SRCS		= fractol.c fractals.c main.c utils.c init_fractal.c image.c
OBJS		= $(SRCS:.c=.o)

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g

# libftprintf
LIBFTPRINTF_DIR	= ft_printf
LIBFTPRINTF		= $(LIBFTPRINTF_DIR)/libftprintf.a
LIBFTPRINTF_FLAGS = -L$(LIBFTPRINTF_DIR) -lftprintf

# libft
LIBFT_DIR	= ft_printf/libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

# minilibx
MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx_linux.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFTPRINTF_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(LIBFTPRINTF): $(LIBFT)
	$(MAKE) -C $(LIBFTPRINTF_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBFTPRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBFTPRINTF_DIR) fclean

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

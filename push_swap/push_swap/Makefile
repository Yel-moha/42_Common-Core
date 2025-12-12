NAME = push_swap

SRCS = main.c input_utils.c validation_utils.c \
    swap_moves.c push_moves.c rotate_moves.c  \
	cycle_sort.c find_min_pos.c sort_three.c \
	insert_utils.c reverse_rotate.c insert_helpers.c \

OBJS = $(SRCS:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -Ift_printf/libft

LIBFT_DIR = ft_printf
LIBFT = $(LIBFT_DIR)/libftprintf.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lftprintf

FT_DIR = ft_printf/libft
FT = $(FT_DIR)/libft.a
FT_FLAGS = -L$(FT_DIR) -lft

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

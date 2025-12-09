NAME_CLIENT = client
NAME_SERVER = server

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_CLIENT = client.c
SRCS_SERVER = server.c

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME_SERVER): $(SRCS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(SRCS_SERVER) -L$(LIBFT_DIR) -lft

$(NAME_CLIENT): $(SRCS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(SRCS_CLIENT) -L$(LIBFT_DIR) -lft

clean:
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

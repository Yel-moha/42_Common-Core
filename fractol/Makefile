# Nome della libreria finale
NAME = fractol

CC = clang
CFLAGS = -Wall -Wextra -Werror -I minilibx_linux

# Sorgenti e oggetti
SRCS = fractol.c
OBJS = $(SRCS:.c=.o)

# Comandi
AR = ar -rcs
RM = rm -f

# Directory della libreria MLX
MLX_DIR = minilibx_linux
MLX_LIB = $(MLX_DIR)/libmlx.a

# Regola principale
all: $(NAME)

# Costruisce la libreria principale
$(NAME): $(OBJS) $(MLX_LIB)
	$(AR) $(NAME) $(OBJS)

# Compila MLX
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

# Regola per compilare i file oggetto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pulisce gli oggetti della libreria locale
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

# Rimuove anche le librerie
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean
	
# Ricostruisce tutto
re: fclean all
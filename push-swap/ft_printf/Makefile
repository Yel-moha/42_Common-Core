# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 21:56:14 by yel-moha          #+#    #+#              #
#    Updated: 2024/12/13 22:14:19 by yel-moha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome della libreria finale
NAME = libftprintf.a

CC = clang
CFLAGS = -Wall -Wextra -Werror -I libft

# Sorgenti e oggetti
SRCS = ft_printf.c handle_char.c handle_hex.c handle_integer.c handle_pointer.c handle_string.c handle_unsigned.c
OBJS = $(SRCS:.c=.o)

# Comandi
AR = ar -rcs
RM = rm -f

# Directory della libreria libft
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Regola principale
all: $(NAME)

# Costruisce la libreria principale
$(NAME): $(OBJS) $(LIBFT_LIB)
	$(AR) $(NAME) $(OBJS)

# Compila libft
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

# Regola per compilare i file oggetto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pulisce gli oggetti della libreria locale
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Rimuove anche le librerie
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	
# Ricostruisce tutto
re: fclean all
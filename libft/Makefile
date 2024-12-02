# Nome del file generato
NAME = libft.a

# Compilatore e opzioni
CC = cc
CFLAGS = -Wall -Wextra -Werror

# File sorgenti
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_calloc.c ft_strdup.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c

# File bonus
BONUS_SRC = ft_lstnew.c 
#ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

# Oggetti generati
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Target di default
all: $(NAME)

# Creazione dell'archivio statico
$(NAME): $(OBJ)
	ar rcs $@ $^
	ranlib $@

# Compilazione dei file .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per il bonus
bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $^
	ranlib $(NAME)

# Pulizia degli oggetti
clean:
	rm -f $(OBJ) $(BONUS_OBJ)

# Pulizia completa
fclean: clean
	rm -f $(NAME)

# Ricostruzione completa
re: fclean all

# Dichiarazione dei target speciali
.PHONY: all clean fclean re bonus
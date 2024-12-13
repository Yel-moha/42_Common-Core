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

NAME = libftprintf.a
FUNC = ft_printf.c ft_print_exadecimal.c ft_print_nbr.c
BFUNC =
OBJ = $(FUNC:.c=.o)
BOBJ = $(BFUNC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all:            $(NAME)

$(NAME): $(OBJ)
        @ar rcs $(NAME) $(OBJ)

%.o: %.c
        @gcc $(FLAGS) -c $< -o $@

clean:
        @rm -f $(OBJ) $(BOBJ)

fclean: clean
        @rm -f $(NAME)

#bonus: $(OBJ) $(BOBJ)                                                                              
#       @ar rcs $(NAME) $(OBJ) $(BOBJ)                                                              

re:             fclean all
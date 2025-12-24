/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:19:11 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/23 17:34:10 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/* 
#include <stdio.h>
#include <ctype.h>

void compare_functions(int c) {
    int my_result = ft_tolower(c);
    int original_result = tolower(c); // A

    printf("Character: %c\n", c);
    printf("My function result: %c\n", my_result);
    printf("Original function result: %c\n", original_result);
}

int main() {
    char test_chars[] = {'A', 'B', 'C', 'a', 'b', '1', '!', 'Z'};
    int i;

    for (i = 0; i < sizeof(test_chars); i++) {
        compare_functions(test_chars[i]);
    }

    return 0;
}
 */
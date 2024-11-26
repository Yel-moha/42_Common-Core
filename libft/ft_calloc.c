/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:34:47 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/26 01:24:08 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libth.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	**num;

	num = (*(sizeof)(char) + 1)*nmemb;
	while (size)
		num = (*(sizeof)(char) + 1)*nmemb;
		
}
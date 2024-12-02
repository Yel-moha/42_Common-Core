/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:34:40 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/02 22:44:41 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	// Allocazione della memoria per il nuovo nodo
	new_node = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_node) // Verifica che malloc abbia avuto successo
		return (NULL);

	// Inizializzazione del contenuto del nodo
	new_node->content = content;

	// Il campo 'next' deve puntare a NULL (è l'ultimo nodo per ora)
	new_node->next = NULL;

	// Restituisci il nodo appena creato
	return (new_node);
}

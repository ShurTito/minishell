/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:57:52 by anttorre          #+#    #+#             */
/*   Updated: 2024/01/25 12:56:35 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief 
 * Mientras que la lista no sea NULL aux es el nodo siguiente de la lista
 * y usamos la funcion lstdelone paasndole la funcion del y despues ponemos
 * el primer nodo de lst en aux cuando llegue a NULL ponemos la lista a NULL
 * 
 * @param lst t_list ** | direccion de memoria de nuestra lista
 * @param del void | puntero a una funcion que elimina
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = aux;
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:41:21 by anttorre          #+#    #+#             */
/*   Updated: 2024/01/10 14:58:03 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ecif(t_env *first_node, t_env **lst, t_env *new)
{
	if (first_node == NULL)
	{
		*lst = new;
		return (EXIT_FAILURE);
	}
	while (first_node->next != NULL)
		first_node = first_node->next;
	first_node->next = new;
	return (EXIT_SUCCESS);
}

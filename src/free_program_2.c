/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_program_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:07:16 by anttorre          #+#    #+#             */
/*   Updated: 2024/02/05 14:34:44 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_mini_lst(t_list **lst)
{
	t_list	*aux;
	int		i;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		i = -1;
		if (((t_mini *)((*lst)->value))->full_cmd)
		{
			while (((t_mini *)((*lst)->value))->full_cmd[++i])
				free(((t_mini *)((*lst)->value))->full_cmd[i]);
		}
		free(((t_mini *)((*lst)->value))->full_cmd);
		free(((t_mini *)((*lst)->value))->full_path);
		if (((t_mini *)((*lst)->value))->infile != 0)
			close(((t_mini *)((*lst)->value))->infile);
		if (((t_mini *)((*lst)->value))->outfile != 1)
			close(((t_mini *)((*lst)->value))->outfile);
		free(((t_mini *)((*lst)->value)));
		free((*lst));
		*lst = aux;
	}
	*lst = NULL;
}

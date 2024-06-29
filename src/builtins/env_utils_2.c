/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:02:35 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/11 16:40:30 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_gstatus_env(t_data *d)
{
	t_env	*aux;
	t_env	*new;
	int		has_oldpwd;

	aux = d->envp;
	has_oldpwd = 0;
	while (aux)
	{
		if (!ft_strncmp2(aux->key, "G_STATUS\0", ft_strlen("G_STATUS\0")))
			has_oldpwd = 1;
		aux = aux->next;
	}
	if (!has_oldpwd)
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return ;
		new->key = ft_strdup("G_STATUS");
		new->value = ft_strjoin_gnl(ft_strdup("="), ft_itoa(g_status));
		new->next = NULL;
		lst_addenv_back(&d->envp, new, NULL);
	}
}

void	update_gstatus(t_data *d)
{
	t_env	*aux;

	aux = d->envp;
	while (aux)
	{
		if (!ft_strncmp2(aux->key, "G_STATUS\0", ft_strlen("G_STATUS\0")))
		{
			free(aux->value);
			aux->value = ft_strjoin_gnl(ft_strdup("="), ft_itoa(g_status));
			break ;
		}
		aux = aux->next;
	}
}

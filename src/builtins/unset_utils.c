/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:02:59 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/14 18:09:44 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lstsize_unset(t_env *lst)
{
	int		i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	check_var_path(t_data *d)
{
	int	i;

	i = -1;
	while (d->env && d->env[++i])
	{
		if (ft_strncmp(d->env[i], "PATH", 4) == 0)
		{
			d->f_path = 1;
			break ;
		}
		else
			d->f_path = 0;
	}
}

void	update_path(t_data *d)
{
	int	i;

	if (d->path != NULL)
		free_bidimensional_array(&d->path);
	i = -1;
	while (d->env[++i])
	{
		if (!ft_strncmp("PATH", d->env[i], 4))
			break ;
	}
	d->path = ft_split(d->env[i] + 5, ':');
	if (!d->path)
		return ;
}

void	update_envp(t_data *d)
{
	t_env	*aux;
	char	*join;
	int		i;
	int		len;

	i = -1;
	free_bidimensional_array(&d->env);
	aux = d->envp;
	len = lstsize_unset(aux);
	d->env = ft_calloc(len + 1, sizeof(char *));
	while (aux)
	{
		d->env[++i] = ft_strdup(aux->key);
		join = d->env[i];
		d->env[i] = ft_strjoin_gnl_2(join, aux->value);
		aux = aux->next;
	}
	check_var_path(d);
	if (d->f_path)
		update_path(d);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:54:03 by anttorre          #+#    #+#             */
/*   Updated: 2024/02/09 11:06:01 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_env_var(t_data *d, char *env_var)
{
	t_env	*aux;

	aux = d->envp;
	while (aux)
	{
		if (!ft_strncmp(aux->key, env_var, ft_strlen(aux->key)))
		{
			d->tmp = ft_strdup(aux->value + 1);
			if (!d->tmp)
				return ;
			break ;
		}
		aux = aux->next;
	}
}

void	update_oldpwd(t_data *d)
{
	t_env	*aux;
	char	dir[500];

	aux = d->envp;
	while (aux)
	{
		if (ft_strncmp(aux->key, "OLDPWD", 6) == 0)
		{
			free(aux->value);
			getcwd(dir, sizeof(dir));
			aux->value = ft_strjoin("=", dir);
			if (!aux->value)
				return ;
			break ;
		}
		aux = aux->next;
	}
}

void	update_oldpwd_2(t_data *d, char *pwd)
{
	t_env	*aux;

	aux = d->envp;
	while (aux)
	{
		if (ft_strncmp(aux->key, "OLDPWD", 6) == 0)
		{
			free(aux->value);
			aux->value = ft_strjoin("=", pwd);
			if (!aux->value)
				return ;
			break ;
		}
		aux = aux->next;
	}
}

void	update_pwd(t_data *d)
{
	t_env	*aux;
	char	dir[500];

	aux = d->envp;
	while (aux)
	{
		if (ft_strncmp(aux->key, "PWD", 3) == 0)
		{
			free(aux->value);
			getcwd(dir, sizeof(dir));
			aux->value = ft_strjoin("=", dir);
			if (!aux->value)
				return ;
			break ;
		}
		aux = aux->next;
	}
}

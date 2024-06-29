/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:42:54 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/11 16:03:51 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tmp(char **tmp)
{
	int	i;

	i = -1;
	if (tmp)
	{
		while (tmp[++i])
			free(tmp[i]);
		free(tmp);
	}
}

int	lstsize_env(t_env *lst)
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

void	lst_addenv_back(t_env **lst, t_env *new, char **tmp)
{
	t_env	*first_node;

	if (new == NULL)
		return ;
	if (tmp != NULL)
	{
		new->key = ft_strdup(tmp[0]);
		if (tmp[1] != NULL)
			new->value = ft_strjoin("=", tmp[1]);
		else
			new->value = ft_strdup("=");
		new->index = 0;
		new->next = NULL;
	}
	first_node = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (first_node->next != NULL)
		first_node = first_node->next;
	first_node->next = new;
}

void	add_oldpwd_env(t_data *d)
{
	t_env	*aux;
	t_env	*new;
	int		has_oldpwd;
	char	actual_dir[500];

	getcwd(actual_dir, 500);
	aux = d->envp;
	has_oldpwd = 0;
	while (aux)
	{
		if (!ft_strncmp2(aux->key, "OLDPWD", ft_strlen("OLDPWD")))
			has_oldpwd = 1;
		aux = aux->next;
	}
	if (!has_oldpwd)
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return ;
		new->key = ft_strdup("OLDPWD");
		new->value = ft_strjoin("=", actual_dir);
		new->next = NULL;
		lst_addenv_back(&d->envp, new, NULL);
	}
	add_gstatus_env(d);
}

void	start_env(t_data *d, char **env)
{
	char	**tmp;

	d->envp = ft_calloc(1, sizeof(t_env));
	if (!d->envp)
		return ;
	tmp = ft_split(env[d->j], '=');
	if (!tmp)
		return ;
	d->envp->key = ft_strdup(tmp[0]);
	d->envp->value = ft_strjoin("=", tmp[1]);
	d->envp->index = 0;
	d->envp->next = NULL;
	free_tmp(tmp);
	while (env[++d->j])
	{
		d->aux = ft_calloc(1, sizeof(t_env));
		if (!d->aux)
			return ;
		tmp = ft_split(env[d->j], '=');
		if (!tmp)
			return ;
		lst_addenv_back(&d->envp, d->aux, tmp);
		free_tmp(tmp);
	}
	add_oldpwd_env(d);
}

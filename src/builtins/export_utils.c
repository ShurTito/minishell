/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:29:10 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/12 17:37:18 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_node(t_env **first_node, t_env *new)
{
	free((*first_node)->value);
	(*first_node)->value = ft_strdup(new->value);
}

void	lst_addexport_back(t_env **lst, t_env *new, char **tmp)
{
	t_env	*first_node;
	t_env	*to_update;
	t_env	*aux;
	int		flag_node;

	aux = NULL;
	flag_node = 0;
	if (new == NULL)
		return ;
	export_conditionals(tmp, new, &to_update);
	first_node = *lst;
	if (*lst == NULL && tmp == NULL)
	{
		*lst = to_update;
		return ;
	}
	if (tmp == NULL)
		ecloop(&first_node, to_update, &flag_node, aux);
	else
		if (ecif(first_node, lst, new) == 1)
			return ;
}

static t_env	*get_max(t_data *d)
{
	t_env	*aux;
	t_env	*max;

	aux = d->envp;
	max = d->envp;
	while (aux)
	{
		if (ft_strncmp(aux->key, max->key, ft_strlen(aux->key) + 1)
			> 0 && aux->index == 0)
			max = aux;
		aux = aux->next;
	}
	return (max);
}

void	set_index_export(t_data *d)
{
	t_env	*lower;
	t_env	*aux;
	int		i;

	i = 1;
	restart_index(&d->envp);
	lower = d->envp;
	aux = d->envp;
	while (i <= lstsize_env(d->envp))
	{
		while (aux)
		{
			if (ft_strncmp(aux->key, lower->key, ft_strlen(aux->key) + 1)
				< 0 && aux->index == 0)
				lower = aux;
			aux = aux->next;
		}
		lower->index = i++;
		aux = d->envp;
		lower = get_max(d);
	}
}

int	add_vars(char *s, t_data *d)
{
	char	**tmp;
	int		i;
	t_env	*new;

	i = 0;
	if (ft_strchr(s, '=') == NULL)
		return (EXIT_SUCCESS);
	while (s[++i])
	{
		if (s[i - 1] != ' ' && s[i] == '=')
		{
			new = ft_calloc(1, sizeof(t_env));
			if (!new)
				return (EXIT_FAILURE);
			tmp = ft_split(s, '=');
			if (!tmp)
				return (EXIT_FAILURE);
			lst_addexport_back(&d->export, new, tmp);
			free_tmp(tmp);
			break ;
		}
		if (s[i - 1] == ' ' && s[i] == '=')
			break ;
	}
	return (check_var_path(d), d->f_var = 1, EXIT_SUCCESS);
}

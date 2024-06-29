/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:05:15 by anttorre          #+#    #+#             */
/*   Updated: 2024/02/06 15:30:42 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restart_index(t_env **lst)
{
	t_env	*aux;

	if (!lst)
		return ;
	aux = *lst;
	while (aux)
	{
		aux->index = 0;
		aux = aux->next;
	}
}

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*st1;
	char	*st2;

	if (s1 == NULL)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	i = 0;
	st1 = (char *)s1;
	st2 = (char *)s2;
	while (i < n && st1[i] != '\0' && st2[i] != '\0' && st1[i] == st2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)st1[i] - (unsigned char)st2[i]);
}

void	exec_export_loop(t_data *d, t_env *head, int *i)
{
	while (*i <= lstsize_env(d->envp))
	{
		while (head)
		{
			if (head->index == *i)
			{
				printf("declare -x %s%s\n", head->key, head->value);
				head = d->envp;
				break ;
			}
			head = head->next;
		}
		(*i)++;
	}
}

void	export_conditionals(char **tmp, t_env *new, t_env **to_update)
{
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
	else
	{
		(*to_update) = ft_calloc(1, sizeof(t_env));
		if (!(*to_update))
			return ;
		(*to_update)->key = ft_strdup(new->key);
		(*to_update)->value = ft_strdup(new->value);
		(*to_update)->index = 0;
		(*to_update)->next = NULL;
	}
}

void	ecloop(t_env **first_node, t_env *to_update, int *flag, t_env *aux)
{
	while (*first_node != NULL)
	{
		if (!ft_strncmp2(to_update->key, (*first_node)->key,
				ft_strlen(to_update->key)))
		{
			del_node(first_node, to_update);
			*flag = 1;
			break ;
		}
		aux = *first_node;
		*first_node = (*first_node)->next;
	}
	if (*flag != 1)
		aux->next = to_update;
	else
	{
		free(to_update->value);
		free(to_update->key);
		free(to_update);
	}
}

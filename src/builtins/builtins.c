/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:41:32 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/13 13:27:53 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_pwd(void)
{
	char	actual_dir[500];

	getcwd(actual_dir, 500);
	printf("%s\n", actual_dir);
}

void	exec_env(t_data *d)
{
	t_env	*head;

	head = d->envp;
	while (head)
	{
		printf("%s%s\n", head->key, head->value);
		head = head->next;
	}
}

void	free_node(t_env **del)
{
	free((*del)->key);
	free((*del)->value);
	free(*del);
}

void	exec_unset(t_data *d, char *key)
{
	t_env	*aux;
	t_env	*del;
	t_env	*prev;

	if (!key)
		return ;
	aux = d->envp;
	prev = NULL;
	while (aux)
	{
		if (!ft_strncmp(aux->key, key, ft_strlen(key)))
		{
			del = aux;
			if (prev)
				prev->next = aux->next;
			else
				d->envp = aux->next;
			free_node(&del);
			break ;
		}
		prev = aux;
		aux = aux->next;
	}
	update_envp(d);
}

void	exec_export(char **s, t_data *d)
{
	t_env	*head;
	t_env	*new;
	int		i;

	set_index_export(d);
	head = d->envp;
	i = 1;
	if (!ft_strncmp(s[0], "export", 6) && !s[1])
		exec_export_loop(d, head, &i);
	else
	{
		new = d->export;
		d->aux = NULL;
		while (new)
		{
			if (!ft_strncmp(new->key, s[1], ft_strlen(new->key)))
				d->aux = new;
			new = new->next;
		}
		lst_addexport_back(&d->envp, d->aux, NULL);
	}
	update_envp(d);
}

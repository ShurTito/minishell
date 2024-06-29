/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:32:55 by anttorre          #+#    #+#             */
/*   Updated: 2024/02/07 12:44:15 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_env(t_env *env)
{
	t_env	*next;

	if (env != NULL)
	{
		while (env)
		{
			next = env->next;
			free(env->key);
			env->key = NULL;
			free(env->value);
			env->value = NULL;
			free(env);
			env = next;
		}
	}
}

void	free_t_list(t_list *lst)
{
	t_list	*next;

	if (lst != NULL)
	{
		while (lst)
		{
			next = lst->next;
			free(lst->value);
			lst->value = NULL;
			free(lst);
			lst = next;
		}
	}
}

void	free_bidimensional_array(char ***s)
{
	int	a;

	if (*s != NULL)
	{
		a = -1;
		while ((*s)[++a] != NULL)
		{
			free((*s)[a]);
			(*s)[a] = NULL;
		}
		free(*s);
		*s = NULL;
	}
}

void	free_all(t_data *d)
{
	free_t_env(d->envp);
	free_t_env(d->export);
	free_t_list(d->cmds);
	d->aux = NULL;
	if (d->env != NULL)
		free_bidimensional_array(&d->env);
	if (d->lexer != NULL)
		free_bidimensional_array(&d->lexer);
	if (d->subsplit != NULL)
		free_bidimensional_array(&d->subsplit);
	if (d->tmp != NULL)
		free(d->tmp);
	if (d->line != NULL)
		free(d->line);
	if (d->tmp1 != NULL)
		free(d->tmp1);
	if (d->shell != NULL)
		free(d->shell);
	if (d->cmds)
		free_t_mini_lst(&d->cmds);
	if (d->here_doc)
		unlink("here_doc.tmp");
	if (d)
		free(d);
}

void	free_dir(char **dir)
{
	int	i;

	i = -1;
	if (dir)
	{
		while (dir[++i])
			free(dir[i]);
		free(dir);
	}
}

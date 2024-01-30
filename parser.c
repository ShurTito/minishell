/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antferna <antferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:30:52 by anttorre          #+#    #+#             */
/*   Updated: 2024/01/30 12:36:24 by antferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_paths(t_data *d, char *s)
{
	char	*tmp;

	if (s[0])
	{
		d->i = 0;
		while (d->env[d->i])
		{
			tmp = ft_strjoin(d->env[d->i], "/");
			d->pchk = ft_strjoin(tmp, s);
			if (!tmp || !d->pchk)
				return (printf("Path check not saved."), NULL);
			free(tmp);
			if (access(d->pchk, F_OK) == 0 && access(d->pchk, X_OK) == 0)
				return (d->pchk);
			free(d->pchk);
			d->pchk = NULL;
			d->i++;
		}
	}
	return (NULL);
}

char	**set_full_cmd(char **s)
{
	int		size;
	char	**arr;
	int		i;

	i = 0;
	size = 0;
	while (s[size] && s[size][0] != '|' && s[size][0] != '>'
		&& s[size][0] != '<')
		size++;
	arr = ft_calloc(size + 1, sizeof(char *));
	while (s[i] && s[i][0] != '|' && s[i][0] != '>'
		&& s[i][0] != '<')
	{
		arr[i] = ft_strdup(s[i]);
		if (!arr[i])
			return (free_bidimensional_array(arr), NULL);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	parse_cmds(t_data *d)
{
	int		i;
	int		j;
	t_mini	*node;

	i = 0;
	while (d->subsplit[i])
	{
		j = 0;
		if (d->subsplit[i][0] != '|')
		{
			node = ft_calloc(1, sizeof(t_mini));
			if (d->subsplit[i][0] != '|' && d->subsplit[i][0] != '>'
				&& d->subsplit[i][0] != '<' && d->subsplit[i])
				node->full_cmd = set_full_cmd(d->subsplit + i);
			while ( d->subsplit[j] && d->subsplit[j][0] != '|' && d->subsplit[j][0] != '>'
				&& d->subsplit[j][0] != '<')
				j++;
			node->full_path = get_paths(d, node->full_cmd[0]);
			node->outfile = d->stdout_cpy;
			node->infile = d->stdin_cpy;
			if (d->subsplit[i][0] == '>' && d->subsplit[i + 1][0] == '>'
				&& d->subsplit[i + 2])
			{
				node->outfile = open(d->subsplit[i + 2], O_WRONLY | O_CREAT
						| O_APPEND, 0644);
				if (node->outfile < 0)
					return ;
			}
			else if (d->subsplit[i][0] == '>' && d->subsplit[i + 1])
			{
				node->outfile = open(d->subsplit[i + 1], O_WRONLY | O_CREAT
						| O_TRUNC, 0644);
				if (node->outfile < 0)
					return ;
			}
			else if (d->subsplit[i][0] == '<' && d->subsplit[i + 1])
			{
				node->infile = open(d->subsplit[i + 1], O_RDONLY);
				if (node->infile < 0)
					return ;
			}
			ft_lstadd_back(&d->cmds, ft_lstnew(node));
		}
		i += j;
		i++;
	}
}

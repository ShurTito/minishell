/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:42:08 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 18:49:50 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser_6_continue(t_data *d, t_mini **node, int i)
{
	if (d->subsplit[i + 1][0] == '>' || d->subsplit[i + 1][0] == '|')
		return (d->clean = ft_lstnew(*node), print_error(NL, NULL),
			g_status = 1, EXIT_FAILURE);
	(*node)->infile = open(d->subsplit[i + 1], O_RDONLY);
	if ((*node)->infile == -1)
	{
		print_error(DIRR, "\0");
		g_status = 1;
	}
	return (EXIT_SUCCESS);
}

void	free_node_2(t_mini *node)
{
	if (node != NULL)
	{
		free_bidimensional_array(&node->full_cmd);
		free(node->full_path);
		free(node);
	}
}

int	parser_8_continue(t_data *d, t_mini **node, int *i)
{
	if (parser_2(d, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (d->subsplit[*i] && d->subsplit[*i][0] != '|'
		&& d->subsplit[*i][0] != '>'
		&& d->subsplit[*i][0] != '<' && d->subsplit[*i])
		(*node)->full_cmd = set_full_cmd(d->subsplit + *i);
	if ((*node)->full_cmd && !(*node)->full_path)
		(*node)->full_path = get_paths(d, (*node)->full_cmd[0]);
	if (d->subsplit[*i] && d->subsplit[*i + 1] && d->subsplit[*i + 1][0] == '|' \
		&& !d->subsplit[*i + 2])
		return (print_error(D_PIPE, NULL), EXIT_FAILURE);
	while (d->subsplit[*i] && d->subsplit[*i][0] != '|'
		&& d->subsplit[*i][0] != '>'
		&& d->subsplit[*i][0] != '<')
		(*i)++;
	return (EXIT_SUCCESS);
}

void	parser_8_continue_2(t_mini **node)
{
	(*node) = ft_calloc(1, sizeof(t_mini));
	(*node)->outfile = 1;
	(*node)->infile = 0;
}

char	*ft_strjoin_gnl_3(char *s1, char *s2)
{
	size_t	s1_length;
	char	*result;
	int		i;

	if (!s1)
	{
		s1 = ft_calloc_gnl(1, sizeof(char));
		if (!s1)
			return (free(s1), s1 = NULL, NULL);
	}
	if (!s1 || !s2)
		return (free(s1), s1 = NULL, NULL);
	s1_length = ft_strlen_gnl(s1);
	result = (char *)ft_calloc_gnl((s1_length + ft_strlen_gnl(s2) + 1),
			sizeof(char));
	if (!result)
		return (free(s1), s1 = NULL, NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[s1_length + i] = s2[i];
	result[s1_length + i] = '\0';
	return (free(s2), s2 = NULL, result);
}

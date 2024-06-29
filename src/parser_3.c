/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:05 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 17:38:54 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser_6(t_data *d, t_mini **node, int i)
{
	if (d->subsplit[i] && d->subsplit[i][0] == '<'
			&& d->subsplit[i + 1][0] == '<')
	{
		if (d->subsplit[i + 2])
		{
			if (d->subsplit[i + 2][0] == '<' || d->subsplit[i + 2][0] == '>')
				return (d->clean = ft_lstnew(*node), print_error(LOWER, NULL)
					, g_status = 1, EXIT_FAILURE);
			else if (d->subsplit[i + 2][0] == '|')
				return (d->clean = ft_lstnew(*node), print_error(D_PIPE, NULL)
					, g_status = 1, EXIT_FAILURE);
			d->f_heredoc = 1;
			here_doc(d, d->subsplit[i + 2]);
			(*node)->infile = d->here_doc;
		}
		else
			return (d->clean = ft_lstnew(*node), print_error(NL, NULL)
				, g_status = 1, EXIT_FAILURE);
	}
	else if (d->subsplit[i] && d->subsplit[i][0] == '<' && d->subsplit[i + 1])
		if (parser_6_continue(d, node, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parser_7(t_data *d, t_mini **node, int *i)
{
	*node = ft_calloc(1, sizeof(t_mini));
	if (d->subsplit[*i] && d->subsplit[*i][0] != '|'
		&& d->subsplit[*i][0] != '>'
		&& d->subsplit[*i][0] != '<' && d->subsplit[*i])
		(*node)->full_cmd = set_full_cmd(d->subsplit + *i);
	if ((*node)->full_cmd)
		(*node)->full_path = get_paths(d, (*node)->full_cmd[0]);
	(*node)->outfile = 1;
	(*node)->infile = 0;
	while (d->subsplit[*i] && d->subsplit[*i][0] != '|'
		&& d->subsplit[*i][0] != '>' && d->subsplit[*i][0] != '<')
		(*i)++;
	return (EXIT_SUCCESS);
}

int	parser_8(t_data *d, t_mini **node, int *i)
{
	parser_8_continue_2(node);
	while (d->subsplit[*i] && d->subsplit[*i + 1]
		&& (d->subsplit[*i][0] == '>' || d->subsplit[*i][0] == '<'))
	{
		if (d->subsplit[*i][0] == '>')
		{
			if ((*node)->outfile != 1)
				close((*node)->outfile);
			if (parser_5(d, node, *i, d->subsplit) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (d->subsplit[*i][0] == '<')
		{
			if ((*node)->infile != 0)
				close((*node)->infile);
			if (parser_6(d, node, *i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (parser_8_continue(d, node, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (d->subsplit[*i + 1] == NULL)
		(*i)++;
	ft_lstadd_back(&d->cmds, ft_lstnew(*node));
	return (EXIT_SUCCESS);
}

int	parser_9_continue(t_data *d, t_mini **node, int *i)
{
	if (parser_7(d, node, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parser_3(d, node, *i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parser_4(d, node, *i, d->subsplit) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parser_2(d, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parser_9(t_data *d, t_mini **node, int *i)
{
	if (parser_9_continue(d, node, i) == EXIT_FAILURE)
		return (free_node_2(*node), EXIT_FAILURE);
	while (d->subsplit[*i] && d->subsplit[*i + 1]
		&& (d->subsplit[*i][0] == '>' || d->subsplit[*i][0] == '<'))
	{
		if (d->subsplit[*i][0] == '>')
		{
			if ((*node)->outfile != 1)
				close((*node)->outfile);
			if (parser_3(d, node, *i) == EXIT_FAILURE)
				return (free_node_2(*node), EXIT_FAILURE);
		}
		else if (d->subsplit[*i][0] == '<')
		{
			if ((*node)->infile != 0)
				close((*node)->infile);
			if (parser_4(d, node, *i, d->subsplit) == EXIT_FAILURE)
				return (free_node_2(*node), EXIT_FAILURE);
		}
		if (parser_2(d, i) == EXIT_FAILURE)
			return (free_node_2(*node), EXIT_FAILURE);
	}
	ft_lstadd_back(&d->cmds, ft_lstnew(*node));
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:53:24 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 14:44:28 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser_2(t_data *d, int *i)
{
	if (d->subsplit[*i])
	{
		if (d->subsplit[*i][0] == '|')
		{
			if (print_pipe_error(i, d) == EXIT_FAILURE)
				return (g_status = 1, EXIT_FAILURE);
			if (d->subsplit[*i + 1] && d->subsplit[*i + 1][0] == '|')
				return (print_error(D_PIPE, NULL), g_status = 1, EXIT_FAILURE);
			d->f_pipe = 1;
			(*i)++;
		}
		else if ((((d->subsplit[*i][0] == '>'
					&& d->subsplit[*i + 1] && d->subsplit[*i + 1][0] == '>'
				&& d->subsplit[*i + 2])
			|| (d->subsplit[*i][0] == '<' && d->subsplit[*i + 1][0] == '<'
			&& d->subsplit[*i + 2]))))
			(*i) += 3;
		else if (d->subsplit[*i][0] == '>' && d->subsplit[*i + 1])
			(*i) += 2;
		else if (d->subsplit[*i][0] == '<' && d->subsplit[*i + 1])
			(*i) += 2;
	}
	return (EXIT_SUCCESS);
}

//cat algo | wc -l >>
int	parser_3(t_data *d, t_mini **node, int i)
{
	if (d->subsplit[i] && d->subsplit[i][0] == '>'
		&& d->subsplit[i + 1] && d->subsplit[i + 1][0] == '>')
	{
		if (d->subsplit[i + 2])
		{
			if (d->subsplit[i + 2][0] == '>' || d->subsplit[i + 2][0] == '|')
				return (d->clean = ft_lstnew(*node), print_error(GREAT, NULL),
					g_status = 1, EXIT_FAILURE);
			(*node)->outfile = open(d->subsplit[i + 2], O_WRONLY | O_CREAT
					| O_APPEND | O_RDONLY, 0644);
			if ((*node)->outfile < 0)
				return (EXIT_FAILURE);
		}
		else
			return (d->clean = ft_lstnew(*node), print_error(NL, NULL),
				g_status = 1, EXIT_FAILURE);
	}
	else if (d->subsplit[i] && d->subsplit[i][0] == '>' && d->subsplit[i + 1])
	{
		(*node)->outfile = open(d->subsplit[i + 1], O_WRONLY | O_CREAT
				| O_RDONLY | O_TRUNC, 0644);
		if ((*node)->outfile < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//cat <<a | wc -l cat <algo | wc -l >>
int	parser_4(t_data *d, t_mini **node, int i, char **sp)
{
	if (sp[i] && sp[i][0] == '<'
			&& sp[i + 1][0] == '<')
	{
		if (sp[i + 2])
		{
			if (sp[i + 2][0] == '<' || sp[i + 2][0] == '>')
				return (d->clean = ft_lstnew(*node), print_error(LOWER, NULL),
					g_status = 1, EXIT_FAILURE);
			else if (sp[i + 2][0] == '|')
				return (d->clean = ft_lstnew(*node), print_error(D_PIPE, NULL),
					g_status = 1, EXIT_FAILURE);
			d->f_heredoc = 1;
			here_doc(d, sp[i + 2]);
			(*node)->infile = d->here_doc;
		}
		else
			return (d->clean = ft_lstnew(*node), print_error(NL, NULL),
				g_status = 1, EXIT_FAILURE);
	}
	else if (sp[i] && sp[i][0] == '<' && sp[i + 1][0] == '|')
		return (d->clean = ft_lstnew(*node), print_error(D_PIPE, NULL),
			g_status = 1, EXIT_FAILURE);
	else if (sp[i] && sp[i][0] == '<' && sp[i + 1])
		(*node)->infile = open(sp[i + 1], O_RDONLY);
	return (EXIT_SUCCESS);
}

//>>>   >><   >>|   >>a
int	parser_5(t_data *d, t_mini **node, int i, char **sp)
{
	if (sp[i] && sp[i][0] == '>' && sp[i + 1] && sp[i + 1][0] == '>')
	{
		if (parser_5_continue(d, node, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (sp[i] && sp[i][0] == '>')
	{
		if (sp[i + 1])
		{
			if (sp[i + 1][0] == '|' || sp[i + 1] == NULL || sp[i + 1][0] == '>'
				|| sp[i + 1][0] == '<')
				return (d->clean = ft_lstnew(*node), print_error(NL, NULL),
					g_status = 1, EXIT_FAILURE);
			(*node)->outfile = open(sp[i + 1], O_RDONLY | O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
			if ((*node)->outfile < 0)
				return (EXIT_FAILURE);
		}
		else
			return (d->clean = ft_lstnew(*node), print_error(NL, NULL),
				g_status = 1, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser_5_continue(t_data *d, t_mini **node, int i)
{
	if (d->subsplit[i + 2])
	{
		if (d->subsplit[i + 2][0] == '>' || d->subsplit[i + 2][0] == '<'
			|| d->subsplit[i + 2][0] == '>')
			return (d->clean = ft_lstnew(*node), print_error(GREAT, NULL)
				, g_status = 1, EXIT_FAILURE);
		else if (d->subsplit[i + 2][0] == '|')
			return (d->clean = ft_lstnew(*node), print_error(D_PIPE, NULL)
				, g_status = 1, EXIT_FAILURE);
		(*node)->outfile = open(d->subsplit[i + 2], O_RDONLY | O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if ((*node)->outfile < 0)
			return (EXIT_FAILURE);
	}
	else
		return (d->clean = ft_lstnew(*node), print_error(NL, NULL)
			, g_status = 1, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

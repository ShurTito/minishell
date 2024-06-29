/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:01:12 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 14:10:25 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(t_data *d, char *delimiter)
{
	d->heredoc = ft_strjoin(delimiter, "\n");
	d->here_doc = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "> ", 2);
		d->here_line = get_next_line(d->stdin_cpy);
		if (!d->here_line)
			msg_err("Line");
		if (!ft_strncmp(d->heredoc, d->here_line, ft_strlen(d->here_line)))
		{
			free(d->heredoc);
			free(d->here_line);
			d->here_line = NULL;
			close(d->stdin_cpy);
			get_next_line(d->stdin_cpy);
			break ;
		}
		write(d->here_doc, d->here_line, ft_strlen(d->here_line));
		free(d->here_line);
	}
	close(d->here_doc);
	d->here_doc = open("here_doc.tmp", O_RDONLY);
	d->stdin_cpy = dup(STDIN_FILENO);
	g_status = 0;
}

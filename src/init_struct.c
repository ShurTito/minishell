/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:45:46 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/14 16:49:06 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *d)
{
	d->env = NULL;
	d->tmp = NULL;
	d->tmp1 = NULL;
	d->shell = NULL;
	d->here_line = NULL;
	d->pchk = NULL;
	d->i = 0;
	d->j = 0;
	d->k = 0;
	d->flag_node = 0;
	d->status = 0;
	d->stdin_cpy = dup(STDIN_FILENO);
	if (!d->stdin_cpy)
		return ;
	d->stdout_cpy = dup(STDOUT_FILENO);
	if (!d->stdout_cpy)
		return ;
	d->f_var = 0;
	d->line = NULL;
	d->f_path = 1;
	d->f_first_time = 1;
	d->f_exit = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:45:40 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/11 18:34:49 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(int n, char *command)
{
	if (n == NL)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (n == D_PIPE)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (n == GREAT)
		printf("bash: syntax error near unexpected token `>'\n");
	else if (n == LOWER)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (n == CMD)
		printf("bash: %s: command not found\n", command);
	else if (n == DIRR)
	{
		printf("bash: %s: No such file or directory\n", command);
		g_status = 1;
	}
	else if (n == PERM)
		printf("bash: permission denied\n");
}

int	print_pipe_error(int *i, t_data *d)
{
	if (d->subsplit[*i + 1] == NULL)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*mini_perror(int err_type, char *param, int err)
{
	g_status = err;
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

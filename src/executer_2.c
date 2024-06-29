/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:49:17 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 18:29:59 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_f_d(t_mini *n)
{
	struct stat	file_info;
	int			i;
	int			j;

	i = 1;
	j = 1;
	while (n->full_cmd[i] && ft_strchr(n->full_cmd[i], '-'))
		i++;
	if (n->full_cmd[i - 1])
	{
		while (n->full_cmd[i - 1][j])
		{
			if (ft_isdigit(n->full_cmd[i - 1][j]))
				return (0);
			j++;
		}
	}
	if (stat(n->full_cmd[i], &file_info) == 0 || !n->full_cmd[i])
		return (1);
	return (0);
}

void	*check_to_fork(t_data *d, t_list *cmd, int fd[2], char **env)
{
	t_mini	*n;
	DIR		*dir;

	n = cmd->value;
	dir = NULL;
	if (n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n->infile == -1 || n->outfile == -1)
		return (g_status = 1, NULL);
	if ((n->full_path && access(n->full_path, X_OK) == 0))
	{
		g_status = exec_fork(d, cmd, fd, env);
		if (!check_f_d(n))
			g_status = 1;
	}
	else if (n->full_cmd && !check_builtin(*n->full_cmd))
	{
		g_status = 127;
		print_error(CMD, ((t_mini *)cmd->value)->full_cmd[0]);
	}
	if (dir)
		closedir(dir);
	return ("");
}

void	*exec_cmd(t_data *d, t_list *cmd, char **env)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (mini_perror(PIPERR, NULL, 1));
	if (!check_to_fork(d, cmd, fd, env))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && !((t_mini *)cmd->next->value)->infile)
		((t_mini *)cmd->next->value)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_mini *)cmd->value)->infile > 2)
		close(((t_mini *)cmd->value)->infile);
	if (((t_mini *)cmd->value)->outfile > 2)
		close(((t_mini *)cmd->value)->outfile);
	return ("");
}

int	builtin(t_data *d, t_list *cmd, char **env)
{
	char	**a;
	t_mini	*n;

	while (cmd)
	{
		a = ((t_mini *)cmd->value)->full_cmd;
		n = ((t_mini *)cmd->value);
		if (a && check_builtin(*a))
			g_status = exec_builtin(n, d);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(d, cmd, env);
		}
		cmd = cmd->next;
	}
	return (g_status);
}

char	*clean_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;

	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

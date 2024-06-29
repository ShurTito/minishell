/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:16:20 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 17:51:22 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtin(t_mini *n, t_data *d)
{
	if (n->full_cmd[0] && !ft_strncmp(n->full_cmd[0], "pwd\0", 4))
		return (exec_pwd(), EXIT_SUCCESS);
	if (n->full_cmd[0] && !ft_strncmp(n->full_cmd[0], "env\0", 4))
		return (exec_env(d), EXIT_SUCCESS);
	if (n->full_cmd[0] && !ft_strncmp(n->full_cmd[0], "unset\0", 6))
		return (exec_unset(d, n->full_cmd[1]), EXIT_SUCCESS);
	if (n->full_cmd[0] && !ft_strncmp(n->full_cmd[0], "export\0", 7))
		return (exec_export(n->full_cmd, d), EXIT_SUCCESS);
	if (n->full_cmd[0] && !ft_strncmp(n->full_cmd[0], "cd\0", 7))
	{
		if (exec_cd(n->full_cmd, d) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (n->full_cmd[0] && !ft_strncmp(n->full_cmd[0], "echo\0", 6))
		return (exec_echo(n->full_cmd, 0), EXIT_SUCCESS);
	if (n->full_cmd[0] && !ft_strncmp(n->full_cmd[0], "exit\0", 5))
	{
		d->l = exec_exit(d);
		if (d->f_exit == 0)
			exit(d->l);
	}
	return (EXIT_FAILURE);
}

int	child_builtin(t_mini *n, char **env, t_data *d)
{
	(void)d;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!check_builtin(*n->full_cmd) && n->full_cmd)
		if (execve(n->full_path, n->full_cmd, env) == -1)
			return (1);
	return (0);
}

void	*child_redir(t_list *cmd, int fd[2])
{
	t_mini	*node;

	node = cmd->value;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (mini_perror(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

int	child_process(t_data *d, t_list *cmd, int fd[2], char **env)
{
	t_mini	*n;

	n = cmd->value;
	child_redir(cmd, fd);
	close(fd[READ_END]);
	if (child_builtin(n, env, d) == 1)
		return (free_t_mini_lst(&d->cmds), 1);
	free_t_mini_lst(&d->cmds);
	exit(g_status);
}

int	exec_fork(t_data *d, t_list *cmd, int fd[2], char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		mini_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
	{
		if (child_process(d, cmd, fd, env) == 1)
			return (1);
	}
	return (EXIT_SUCCESS);
}

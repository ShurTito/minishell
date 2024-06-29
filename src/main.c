/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:12:26 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 18:54:18 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unlink_tmp(t_data *d)
{
	if (d->f_heredoc)
		unlink("here_doc.tmp");
	d->f_heredoc = 0;
}

/*
	t_list *aux;
	aux = d->cmds;
	while (aux)
	{
		i = 0;
		printf("full_path:%s\n", ((t_mini *)(aux->value))->full_path);
		if (((t_mini *)(aux->value))->full_cmd)
		{
			while (((t_mini *)(aux->value))->full_cmd[i])
			{
				printf("cmd %i:%s\n", i, ((t_mini *)(aux->value))->full_cmd[i]);
				i++;
			}
		}
		printf("Outfile: %d\nInfile: %d\n\n", ((t_mini *)(aux->value))->outfile,
		((t_mini *)(aux->value))->infile);
		aux = aux->next;
	}
	int i = -1;
	while (d->subsplit[++i])
		printf("d->subsplit[%d] = %s\n", i, d->subsplit[i]);
	//lexer_2(d);
*/

int	process_input(char *input, t_data *d, char **env)
{
	update_envp(d);
	if (check_quotes(input) == EXIT_FAILURE)
		return (printf("Wrong input. Close quotes.\n"), EXIT_SUCCESS);
	d->lexer = ft_split_mini(input, ' ');
	if (!d->lexer)
		return (EXIT_SUCCESS);
	expand_var(d);
	d->subsplit = split_pipe_redir(d->lexer, -1, 0, d);
	if (!d->subsplit)
		return (free_bidimensional_array(&d->lexer), EXIT_SUCCESS);
	if (parse_cmds(d) == EXIT_FAILURE)
		return (free_t_mini_lst(&d->cmds), EXIT_SUCCESS);
	if (!d->f_pipe)
		if (add_vars(input, d) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	d->j = ft_lstsize(d->cmds);
	if (!d->f_var)
		g_status = builtin(d, d->cmds, env);
	while (d->j-- > 0)
		waitpid(-1, &d->status, 0);
	if (g_status == 13)
		g_status = 0;
	update_gstatus(d);
	return (EXIT_SUCCESS);
}

int	minishell(char **env, t_data *d)
{
	if (get_env_paths(env, d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	start_env(d, env);
	while (1)
	{
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, SIG_IGN);
		if (prompt(&d->line, d, 0) == EXIT_FAILURE)
			return (free(d->line), EXIT_FAILURE);
		if (ft_strncmp(d->line, "\0", 1))
			add_history(d->line);
		if (process_input(d->line, d, env) == EXIT_FAILURE)
			return (free(d->line), EXIT_FAILURE);
		if (d->lexer != NULL)
			free_bidimensional_array(&d->lexer);
		if (d->subsplit != NULL)
			free_bidimensional_array(&d->subsplit);
		if (d->cmds != NULL)
			free_t_mini_lst(&d->cmds);
		free(d->line);
		unlink_tmp(d);
		d->f_pipe = 0;
		d->f_var = 0;
	}
	return (rl_clear_history(), EXIT_SUCCESS);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc > 1)
		exit(EXIT_FAILURE);
	(void) argv;
	(void) argc;
	atexit(ft_leaks);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(g_status);
	init_struct(data);
	minishell(env, data);
	exit(g_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antferna <antferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:55 by anttorre          #+#    #+#             */
/*   Updated: 2024/01/30 12:14:30 by antferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_input(char *input, t_data *d, char **env)
{
	(void) env;
	d->lexer = ft_split_mini(input, ' ');
	if (!d->lexer)
		return (EXIT_SUCCESS);
	expand_var(d);
	d->subsplit = split_pipe_redir(d->lexer, -1, 0, d);
	if (!d->subsplit)
		return (free_bidimensional_array(d->lexer), EXIT_SUCCESS);
	parse_cmds(d);
	t_list *aux;

	aux = d->cmds;
	int i;
	while (aux)
	{
		i = 0;
		printf("full_path:%s\n", ((t_mini *)(aux->value))->full_path);
		while (((t_mini *)(aux->value))->full_cmd[i])
		{
			printf("cmd %i:%s\n", i, ((t_mini *)(aux->value))->full_cmd[i]);
			i++;
		}
		aux = aux->next;
	}
	if (!d->f_pipe)
		if (add_vars(input, d) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (!ft_strncmp(d->subsplit[0], "pwd\0", 4))
		exec_pwd();
	if (!ft_strncmp(d->subsplit[0], "env\0", 4))
		exec_env(d);
	if (!ft_strncmp(d->subsplit[0], "unset\0", 6))
		exec_unset(d, d->subsplit[1]);
	if (!ft_strncmp(d->subsplit[0], "export\0", 7))
		exec_export(d->subsplit, d);
	if (!ft_strncmp(d->subsplit[0], "cd\0", 7))
		exec_cd(d->subsplit, d);
	if (!ft_strncmp(d->subsplit[0], "echo\0", 6))
		exec_echo(d->subsplit, 0);
	if (!ft_strncmp(d->subsplit[0], "exit\0", 5))
		exec_exit();
	return (EXIT_SUCCESS);
}

int	minishell(char **env, t_data *d)
{
	d->line = NULL;
	if (get_env_paths(env, d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	start_env(d, env);
	while (1)
	{
		if (prompt(&d->line, d) == EXIT_FAILURE)
			return (free(d->line), EXIT_FAILURE);
		if (ft_strncmp(d->line, "\0", 1))
			add_history(d->line);
		if (process_input(d->line, d, env) == EXIT_FAILURE)
			return (free(d->line), EXIT_FAILURE);
		if (!d->line)
			clear_history();
		if (d->lexer != NULL)
			free_bidimensional_array(d->lexer);
		if (d->subsplit != NULL)
			free_bidimensional_array(d->subsplit);
		free(d->line);
		d->line = NULL;
	}
	if (d->line)
		free(d->line);
	return (EXIT_SUCCESS);
}

void ft_leaks()
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void) argv;
	(void) argc;
	atexit(ft_leaks);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	init_struct(data);
	if (minishell(env, data) == EXIT_FAILURE)
	{
		free_all(data);
		exit(EXIT_FAILURE);	
	}
	free_all(data);
	exit(EXIT_SUCCESS);
}

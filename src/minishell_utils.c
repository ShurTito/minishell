/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:56:26 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/13 12:11:15 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_paths(char **env, t_data *d)
{
	d->i = 0;
	if (d->f_path)
	{
		if (d->env != NULL)
			free_bidimensional_array(&d->env);
		if (d->path != NULL)
			free_bidimensional_array(&d->path);
		d->i = 0;
		while (env[d->i])
			d->i++;
		d->env = ft_calloc(d->i + 1, sizeof(char *));
		d->i = -1;
		while (env[++d->i])
			d->env[d->i] = ft_strdup(env[d->i]);
		d->i = -1;
		while (d->env[++d->i])
		{
			if (!ft_strncmp("PATH", d->env[d->i], 4))
				break ;
		}
		d->path = ft_split(d->env[d->i] + 5, ':');
		if (!d->path)
			return (EXIT_FAILURE);
	}
	return (d->i = 0, EXIT_SUCCESS);
}

int	prompt(char **line, t_data *d, int i)
{
	char	cur_dir[500];
	char	**dir;

	dir = ft_split(getcwd(cur_dir, sizeof(cur_dir)), '/');
	if (!dir)
		return (free_dir(dir), EXIT_FAILURE);
	while (dir[i])
		i++;
	if (i < 1)
		d->tmp = ft_strjoin(YELLOW_T, "/");
	else
		d->tmp = ft_strjoin(YELLOW_T, dir[i - 1]);
	free_dir(dir);
	d->shell = ft_strjoin_gnl_2(ft_strjoin(BLUE_T, "minishell@"), d->tmp);
	if (!d->tmp || !d->shell)
		return (free(d->tmp), free(d->shell), 1);
	free(d->tmp);
	d->tmp = ft_strjoin(d->shell, RESET_COLOR "\x1b[1;31m ▸ \x1b[0m");
	if (!d->tmp)
		return (free(d->shell), EXIT_FAILURE);
	*line = readline(d->tmp);
	if (!*line)
		return (free(d->tmp), free(d->shell), EXIT_FAILURE);
	return (free(d->tmp), free(d->shell), d->tmp = NULL, d->tmp1 = NULL, 0);
}

static void	expand_c1(t_data *d, int *flag, char **res, int *i)
{
	char	*s;

	if (d->lexer[d->i][d->j] == '$' && !*flag)
	{
		if (d->lexer[d->i][d->j + 1] == '\0' || d->lexer[d->i][d->j + 1] == ' ')
		{
			*res = ft_strjoin_gnl(*res, ft_strdup("$"));
			d->j++;
		}
		else if (d->lexer[d->i][d->j + 1] == '?')
			expand_global_status(d, res);
		else
		{
			d->j++;
			*i = d->j;
			while ((d->lexer[d->i][d->j] != ' ' && d->lexer[d->i][d->j] != '$'
				&& d->lexer[d->i][d->j] != '\0') && d->lexer[d->i][d->j] != '\''
					&& d->lexer[d->i][d->j] != '\"')
				d->j++;
			s = ft_substr(d->lexer[d->i], *i, d->j - *i);
			*res = ft_strjoin_gnl(*res, get_value_env(d, s));
			free(s);
			s = NULL;
		}
	}
}

static void	expand_c2(t_data *d, int *flag, char **res, int *i)
{
	d->f_double = 0;
	if ((!*flag && d->lexer[d->i][d->j] == '~')
		&& ((d->lexer[d->i][d->j - 1] == ' ' && d->lexer[d->i][d->j + 1] == ' ')
		|| (d->lexer[d->i][d->j + 1] == '\0')
		|| (d->lexer[d->i][d->j + 1] == '/')))
	{
		if (d->lexer[d->i][d->j] == '\'')
			*flag = !*flag;
		*res = ft_strjoin_gnl(*res, get_value_env(d, "HOME"));
		d->j++;
	}
	else
	{
		*i = d->j;
		while ((d->lexer[d->i][d->j] != '$' || *flag)
			&& d->lexer[d->i][d->j] != '\0')
		{
			if (d->lexer[d->i][d->j] == '\"')
				d->f_double = !d->f_double;
			if (d->lexer[d->i][d->j] == '\'' && !d->f_double)
				*flag = !*flag;
			d->j++;
		}
		*res = ft_strjoin_gnl(*res, ft_substr(d->lexer[d->i], *i, d->j - *i));
	}
}

void	expand_var(t_data *d)
{
	int		i;
	char	*res;
	int		flag;

	d->i = -1;
	flag = 0;
	res = NULL;
	while (d->lexer[++d->i])
	{
		d->j = 0;
		i = 0;
		while (d->lexer[d->i][d->j])
		{
			expand_c1(d, &flag, &res, &i);
			expand_c2(d, &flag, &res, &i);
		}
		free(d->lexer[d->i]);
		d->lexer[d->i] = NULL;
		d->lexer[d->i] = ft_strdup(res);
		free(res);
		res = NULL;
	}
	d->i = 0;
}

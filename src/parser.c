/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:30:52 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 18:50:09 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "pwd\0", ft_strlen("pwd\0")))
		return (1);
	if (!ft_strncmp(s, "echo\0", ft_strlen("echo\0")))
		return (1);
	if (!ft_strncmp(s, "env\0", ft_strlen("env\0")))
		return (1);
	if (!ft_strncmp(s, "unset\0", ft_strlen("unset\0")))
		return (1);
	if (!ft_strncmp(s, "exit\0", ft_strlen("exit\0")))
		return (1);
	if (!ft_strncmp(s, "export\0", ft_strlen("export\0")))
		return (1);
	if (!ft_strncmp(s, "cd\0", ft_strlen("cd\0")))
		return (1);
	return (0);
}

int	check_existing_path(char *s)
{
	if (access(s, F_OK) == 0 && access(s, X_OK) == 0)
		return (free(s), 1);
	return (free(s), 0);
}
/* if (!tmp || !d->pchk)
	return (printf("Path check not saved."), NULL); */

char	*get_paths(t_data *d, char *s)
{
	char	*tmp;

	if (check_existing_path(clean_quotes(s)))
		return (clean_quotes(s));
	if (d->f_path)
	{
		if (s[0])
		{
			if (check_builtin_2(clean_quotes(s)))
				return (ft_strdup("builtin"));
			d->i = -1;
			while (d->path[++d->i])
			{
				tmp = ft_strjoin(d->path[d->i], "/");
				d->pchk = ft_strjoin_gnl_3(tmp, clean_quotes(s));
				free(tmp);
				if (access(d->pchk, F_OK) == 0 && access(d->pchk, X_OK) == 0)
					return (d->pchk);
				free(d->pchk);
				d->pchk = NULL;
			}
		}
	}
	return (NULL);
}

char	**set_full_cmd(char **s)
{
	int		size;
	char	**arr;
	int		i;

	i = 0;
	size = 0;
	while (s[size] && s[size][0] != '|' && s[size][0] != '>'
		&& s[size][0] != '<')
		size++;
	arr = ft_calloc(size + 1, sizeof(char *));
	while (s[i] && s[i][0] != '|' && s[i][0] != '>' && s[i][0] != '<')
	{
		arr[i] = clean_quotes(s[i]);
		if (!arr[i])
			return (free_bidimensional_array(&arr), NULL);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	parse_cmds(t_data *d)
{
	d->l = 0;
	while (d->subsplit[d->l])
	{
		if (d->subsplit[d->l][0] != '|' && d->subsplit[d->l][0] != '<'
			&& d->subsplit[d->l][0] != '>')
		{
			if (parser_9(d, &d->node, &d->l) == EXIT_FAILURE)
				return (free_t_mini_lst(&d->clean), EXIT_FAILURE);
		}
		else if (d->subsplit[d->l] && (d->subsplit[d->l][0] == '<'
			|| d->subsplit[d->l][0] == '>'))
		{
			if (parser_8(d, &d->node, &d->l) == EXIT_FAILURE)
				return (free_t_mini_lst(&d->clean), EXIT_FAILURE);
		}
		else
		{
			if ((d->subsplit[d->l + 1] && d->subsplit[d->l + 1][0] == '|') \
				|| (d->subsplit[d->l][0] == '|' && !d->subsplit[d->l + 1]))
				return (print_error(D_PIPE, NULL), g_status = 1, EXIT_FAILURE);
			d->l++;
		}
	}
	return (EXIT_SUCCESS);
}

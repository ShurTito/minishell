/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:26:02 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 18:50:28 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_len(char *s)
{
	size_t	len;
	int		i;
	int		fq_simple;
	int		fq_double;

	len = 0;
	i = -1;
	fq_simple = 0;
	fq_double = 0;
	while ((s[++i] || (fq_double || fq_simple)))
	{
		if (s[i] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		else if (s[i] == '\"' && !fq_simple)
			fq_double = !fq_double;
		else
			len++;
	}
	return (len);
}

void	ft_copy(char *s1, char *s2)
{
	int		i;
	int		j;
	int		fq_simple;
	int		fq_double;

	i = 0;
	j = 0;
	fq_simple = 0;
	fq_double = 0;
	while (s1[i])
	{
		if (s1[i] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		else if (s1[i] == '\"' && !fq_simple)
			fq_double = !fq_double;
		else
			s2[j++] = s1[i];
		i++;
	}
	s2[j] = '\0';
}

void	lexer_2(t_data *d)
{
	int		size;
	int		i;
	char	*aux;

	i = -1;
	while (d->lexer[++i])
	{
		size = 0;
		size = word_len(d->lexer[i]);
		aux = ft_calloc(size + 1, 1);
		ft_copy(d->lexer[i], aux);
		free(d->lexer[i]);
		d->lexer[i] = ft_strdup(aux);
		free(aux);
	}
}

int	check_quotes(char *s)
{
	int		i;
	int		fq_simple;
	int		fq_double;

	i = 0;
	fq_simple = 0;
	fq_double = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		else if (s[i] == '\"' && !fq_simple)
			fq_double = !fq_double;
		i++;
	}
	if (fq_double || fq_simple)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_builtin_2(char *s)
{
	if (!ft_strncmp(s, "pwd\0", ft_strlen("pwd\0")))
		return (free(s), 1);
	if (!ft_strncmp(s, "echo\0", ft_strlen("echo\0")))
		return (free(s), 1);
	if (!ft_strncmp(s, "env\0", ft_strlen("env\0")))
		return (free(s), 1);
	if (!ft_strncmp(s, "unset\0", ft_strlen("unset\0")))
		return (free(s), 1);
	if (!ft_strncmp(s, "exit\0", ft_strlen("exit\0")))
		return (free(s), 1);
	if (!ft_strncmp(s, "export\0", ft_strlen("export\0")))
		return (free(s), 1);
	if (!ft_strncmp(s, "cd\0", ft_strlen("cd\0")))
		return (free(s), 1);
	return (free(s), 0);
}

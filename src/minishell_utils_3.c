/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:08:54 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 16:43:31 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_split(char **arr, size_t index)
{
	size_t	i;

	if (arr != NULL)
	{
		i = 0;
		while (i < index)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

static void	cw2(char **s, int *f_simp, int *f_double, t_data *d)
{
	if (s[d->i][d->j] == '\'' && !*f_double)
	{
		if (*f_simp)
		{
			d->count++;
			d->f_word = 0;
		}
		*f_simp = !*f_simp;
	}
	if (s[d->i][d->j] == '\"' && !*f_simp)
	{
		if (*f_double)
		{
			d->count++;
			d->f_word = 0;
		}
		*f_double = !*f_double;
	}
	if (s[d->i][d->j] != '\'' && s[d->i][d->j] != '\"' && s[d->i][d->j] != '<'
		&& s[d->i][d->j] != '|' && s[d->i][d->j] != '>' && d->f_word && !*f_simp
		&& !*f_double)
	{
		d->count++;
		d->f_word = !d->f_word;
	}
}

static int	words_count(char **s, t_data *d)
{
	int	f_simp;
	int	f_double;

	f_simp = 0;
	f_double = 0;
	d->i = -1;
	d->count = 0;
	while (s[++d->i])
	{
		d->j = -1;
		d->f_word = 1;
		while (s[d->i][++d->j])
		{
			cw2(s, &f_simp, &f_double, d);
			if ((s[d->i][d->j] == '<' || s[d->i][d->j] == '|'
				|| s[d->i][d->j] == '>') && !f_simp && !f_double)
			{
				d->count++;
				d->f_word = 1;
			}
		}
	}
	return (d->count);
}

static int	word_length(char *s)
{
	int	f_simp;
	int	f_double;
	int	i;
	int	len;

	f_simp = 0;
	f_double = 0;
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && !f_double)
			f_simp = !f_simp;
		if (s[i] == '\"' && !f_simp)
			f_double = !f_double;
		if ((s[i] == '<' || s[i] == '|' || s[i] == '>') && !f_simp && !f_double)
			return (1);
		else if ((s[i] != '<' && s[i] != '|' && s[i] != '>') || f_simp
			|| f_double)
			len++;
		if ((s[i + 1] == '<' || s[i + 1] == '>' || s[i + 1] == '|') && (!f_simp
				&& !f_double))
			return (len);
	}
	return (len);
}

char	**split_pipe_redir(char **s, int p, int h, t_data *d)
{
	char	**new_s;

	d->w = 0;
	new_s = ft_calloc(words_count(s, d) + 1, sizeof(char *));
	if (!new_s)
		return (NULL);
	while (s[++p])
	{
		h = 0;
		while (s[p][h])
		{
			if (s[p][h] == '\0')
				break ;
			d->word_len = word_length(s[p] + h);
			new_s[d->w] = ft_substr(s[p], h, d->word_len);
			if (!new_s[d->w])
				return (ft_free_split(new_s, d->w), NULL);
			h += d->word_len;
			d->w++;
		}
	}
	if (s[0] && s[0][0] == '\0')
		new_s[d->w++] = ft_strdup("");
	return (new_s[d->w] = NULL, new_s);
}

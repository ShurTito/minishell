/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:21:31 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/12 14:39:16 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	msg_err(char *str)
{
	perror(str);
	unlink("here_doc.tmp");
	return (EXIT_FAILURE);
}

void	expand_global_status(t_data *d, char **res)
{
	*res = ft_strjoin_gnl(*res, get_value_env(d, "G_STATUS"));
	d->j += 2;
}

size_t	ft_strlen2(const char *s)
{
	size_t	count;

	count = 0;
	if (!s)
		return (count);
	while (s[count] != '\0')
		count++;
	return (count);
}

int	ft_strlen_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\"' && s[i] != '\'')
		i++;
	return (i);
}

char	*get_value_env(t_data *d, char *key)
{
	t_env	*aux;

	aux = d->envp;
	while (aux)
	{
		if (!ft_strncmp(aux->key, key, ft_strlen(key) + 1))
			return (ft_strdup(aux->value + 1));
		aux = aux->next;
	}
	return (ft_strdup(""));
}

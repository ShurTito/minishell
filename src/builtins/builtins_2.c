/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:10:39 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 17:06:57 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* OLD BUT GOLD
int	exec_cd(char **s, t_data *d)
{
	int		flag;
	char	dir[500];

	if (!ft_strncmp(s[0], "cd\0", 3) && s[1] == NULL)
	{
		get_env_var(d, "HOME");
		update_oldpwd(d);
		chdir(d->tmp);
		update_pwd(d);
	}
	else if (!ft_strncmp(s[0], "cd\0", 3) && !ft_strncmp(s[1], "-\0", 2))
	{
		get_env_var(d, "OLDPWD");
		update_oldpwd(d);
		chdir(d->tmp);
		update_pwd(d);
	}
	else if (!ft_strncmp(s[0], "cd\0", 3) && s[1])
	{
		getcwd(dir, sizeof(dir));
		flag = chdir(s[1]);
		if (flag == -1)
		{
			d->tmp = ft_strjoin("bash: cd: ", s[1]);
			if (!d->tmp)
				return (EXIT_FAILURE);
			d->tmp1 = ft_strjoin(d->tmp, ": No such file or directory");
			free(d->tmp);
			if (!d->tmp1)
				return (EXIT_FAILURE);
			ft_putendl_fd(d->tmp1, 2);
			free(d->tmp1);
			return (EXIT_FAILURE);
		}
		else if (flag == 0)
		{
			update_oldpwd_2(d, dir);
			update_pwd(d);
		}
	}
	free(d->tmp);
	d->tmp = NULL;
	free(d->tmp1);
	d->tmp1 = NULL;
	return (EXIT_SUCCESS);
}
*/

int	change_directory(char *path, t_data *d)
{
	char	dir[500];
	int		flag;

	getcwd(dir, sizeof(dir));
	flag = chdir(path);
	if (flag == -1)
	{
		d->tmp = ft_strjoin("bash: cd: ", path);
		if (!d->tmp)
			return (EXIT_FAILURE);
		d->tmp1 = ft_strjoin(d->tmp, ": No such file or directory");
		free(d->tmp);
		if (!d->tmp1)
			return (EXIT_FAILURE);
		ft_putendl_fd(d->tmp1, 2);
		free(d->tmp1);
		return (EXIT_FAILURE);
	}
	else if (flag == 0)
	{
		update_oldpwd_2(d, dir);
		update_pwd(d);
	}
	return (EXIT_SUCCESS);
}

int	exec_cd(char **s, t_data *d)
{
	if (!ft_strncmp(s[0], "cd\0", 3) && s[1] == NULL)
	{
		get_env_var(d, "HOME");
		update_oldpwd(d);
		chdir(d->tmp);
		update_pwd(d);
	}
	else if (!ft_strncmp(s[0], "cd\0", 3) && !ft_strncmp(s[1], "-\0", 2))
	{
		get_env_var(d, "OLDPWD");
		update_oldpwd(d);
		chdir(d->tmp);
		update_pwd(d);
	}
	else if (!ft_strncmp(s[0], "cd\0", 3) && s[1])
	{
		if (change_directory(s[1], d) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	free(d->tmp);
	d->tmp = NULL;
	free(d->tmp1);
	d->tmp1 = NULL;
	return (EXIT_SUCCESS);
}

void	exec_echo_2(char **s, int *f_simp, int *f_double, int size)
{
	int	i;

	*f_simp = 0;
	*f_double = 0;
	i = 0;
	while (s[size][i])
	{
		if (s[size][i] == '\'' && !*f_double)
			*f_simp = !*f_simp;
		if (s[size][i] == '\"' && !*f_simp)
			*f_double = !*f_double;
		if ((s[size][i] == '\'' && *f_double) || (s[size][i] == '\"' && *f_simp)
			|| (s[size][i] != '\'' && s[size][i] != '\"' ))
			printf("%c", s[size][i]);
		if (s[size][i] == '\0')
			break ;
		i++;
	}
}

void	exec_echo(char **s, int option)
{
	int	size;
	int	f_simp;
	int	f_double;

	size = 0;
	f_simp = 0;
	f_double = 0;
	while (s[size])
		size++;
	if (size > 1)
	{
		size = 0;
		while (s[++size] && !ft_strncmp(s[size], "-n", 2))
			option = 1;
		while (s[size])
		{
			exec_echo_2(s, &f_simp, &f_double, size);
			if (s[size + 1] || s[size][0] == '\0')
				printf(" ");
			size++;
		}
	}
	if (option == 0)
		printf("\n");
}

int	exec_exit(t_data *d)
{
	t_mini	*n;
	int		i;

	n = d->cmds->value;
	if (d->f_heredoc)
		unlink("here_doc.tmp");
	free_bidimensional_array(&d->path);
	if (!n->full_cmd[1])
		printf("exit\n");
	else if (n->full_cmd[2])
		return (d->f_exit = 1, printf("bash: exit: too many arguments\n"), 1);
	else if (n->full_cmd[1] && !n->full_cmd[2])
	{
		i = 0;
		while (n->full_cmd[1][i])
		{
			if (!ft_isdigit(n->full_cmd[1][i]))
				return (d->f_exit = 0,
					printf("bash: numeric argument required\n"), 255);
			i++;
		}
		return (d->f_exit = 0, ft_atoi(n->full_cmd[1]));
	}
	free_t_mini_lst(&d->cmds);
	return (d->f_exit = 0, 0);
}

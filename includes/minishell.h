/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:14:39 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 18:42:21 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/ft_printf.h"
# include "../libft/get_next_line_bonus.h"
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# define WHITE_T "\x1b[1;37m"
# define YELLOW_T "\x1b[1;33m"
# define RESET_COLOR "\x1b[0m"
# define BLUE_T "\x1b[1;36m"
# define NL 2
# define D_PIPE 3
# define GREAT 4
# define LOWER 5
# define CMD 6
# define DIRR 7
# define PERM 8
# define WRITE_END 1
# define READ_END 0

int	g_status;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	struct s_env	*next;
}			t_env;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}		t_mini;

typedef struct s_data
{
	char			**env;
	char			**path;
	char			*tmp;
	char			*line;
	char			*here_line;
	char			*tmp1;
	char			*shell;
	int				i;
	int				j;
	int				k;
	t_mini			*node;
	int				l;
	int				count;
	int				f_word;
	int				f_pipe;
	int				f_exit;
	int				f_heredoc;
	int				here_doc;
	t_env			*envp;
	t_env			*aux;
	t_list			*clean;
	t_list			*aux2;
	t_env			*export;
	int				flag_node;
	char			**lexer;
	char			**subsplit;
	int				stdin_cpy;
	int				stdout_cpy;
	t_list			*cmds;
	int				w;
	int				word_len;
	int				h;
	char			*pchk;
	pid_t			pid;
	int				status;
	struct termios	old_termios;
	int				f_var;
	char			*heredoc;
	int				fd[2];
	int				f_double;
	int				f_path;
	int				f_first_time;
}			t_data;

/*--- FREE_PROGRAM.c ---*/
void		free_all(t_data *d);
void		free_dir(char **dir);
void		free_bidimensional_array(char ***s);

/*--- FREE_PROGRAM_2.c ---*/
void		free_t_mini_lst(t_list **lst);

/*--- INIT_STRUCT.c ---*/
void		init_struct(t_data *d);

/*--- MAIN.c ---*/
void		unlink_tmp(t_data *d);
int			process_input(char *input, t_data *d, char **envp);

/*--- MINISHELL_UTILS.c ---*/
int			get_env_paths(char **env, t_data *d);
int			prompt(char **line, t_data *d, int i);
int			prompt(char **line, t_data *d, int i);
void		expand_var(t_data *d);

/*--- MINISHELL_UTILS_2.c ---*/
int			msg_err(char *str);
char		*get_value_env(t_data *d, char *key);
int			ft_strlen_space(char *s);
size_t		ft_strlen2(const char *s);
void		expand_global_status(t_data *d, char **res);

/*--- MINISHELL_UTILS_3.c ---*/
char		**split_pipe_redir(char **s, int p, int h, t_data *d);

/*--- ENV_UTILS.c ---*/
void		start_env(t_data *d, char **env);
void		lst_addenv_back(t_env **lst, t_env *new, char **tmp);
int			lstsize_env(t_env *lst);
void		free_tmp(char **tmp);

/*--- ENV_UTILS_2.c ---*/
void		add_gstatus_env(t_data *d);
void		update_gstatus(t_data *d);

/*--- BUILTINS.c ---*/
void		exec_pwd(void);
void		exec_env(t_data *d);
void		exec_unset(t_data *d, char *key);
void		exec_export(char **s, t_data *d);

/*--- UNSET_UTILS.c ---*/
int			lstsize_unset(t_env *lst);
void		update_envp(t_data *d);
void		check_var_path(t_data *d);

/*--- BUILTINS_2.c ---*/
void		exec_echo(char **s, int option);
int			exec_cd(char **s, t_data *d);
int			exec_exit(t_data *d);
void		update_envp(t_data *d);

/*--- EXPORT_UTILS.c ---*/
int			add_vars(char *s, t_data *d);
void		set_index_export(t_data *d);
void		lst_addexport_back(t_env **lst, t_env *new, char **tmp);
void		del_node(t_env **first_node, t_env *new);

/*--- EXPORT_UTILS_2.c ---*/
void		restart_index(t_env	**lst);
void		exec_export_loop(t_data *d, t_env *head, int *i);
void		export_conditionals(char **tmp, t_env *new, t_env **to_update);
int			ft_strncmp2(const char *s1, const char *s2, size_t n);
void		ecloop(t_env **first_node, t_env *to_update, int *flag, t_env *aux);

/*--- EXPORT_UTILS_3.c ---*/
int			ecif(t_env *first_node, t_env **lst, t_env *new);

/*--- CD_UTILS.c ---*/
void		get_env_var(t_data *d, char *env_var);
void		update_pwd(t_data *d);
void		update_oldpwd(t_data *d);
void		update_oldpwd_2(t_data *d, char *pwd);

/*--- FT_SPLIT_MINI.c ---*/
char		**ft_split_mini(const char *s, char delimiter);

/*--- PARSER.c ---*/
int			parse_cmds(t_data *d);
char		*get_paths(t_data *d, char *s);
char		**set_full_cmd(char **s);
int			check_builtin(char *s);

/*--- PARSER_2.c ---*/
int			parser_2(t_data *d, int *i);
int			parser_3(t_data *d, t_mini **node, int i);
int			parser_4(t_data *d, t_mini **node, int i, char **sp);
int			parser_5(t_data *d, t_mini **node, int i, char **sp);
int			parser_5_continue(t_data *d, t_mini **node, int i);

/*--- PARSER_3.c ---*/
int			parser_6(t_data *d, t_mini **node, int i);
int			parser_7(t_data *data, t_mini **node, int *i);
int			parser_8(t_data *d, t_mini **node, int *i);
int			parser_9(t_data *d, t_mini **node, int *i);

/*--- PARSER_4.c ---*/
int			parser_6_continue(t_data *d, t_mini **node, int i);
void		free_node_2(t_mini *node);
int			parser_8_continue(t_data *d, t_mini **node, int *i);
void		parser_8_continue_2(t_mini **node);
char		*ft_strjoin_gnl_3(char *s1, char *s2);

/*--- HERE_DOC.c ---*/
void		here_doc(t_data *d, char *delimiter);

/*--- ERROR_MESSAGES.c ---*/
void		print_error(int n, char *command);
int			print_pipe_error(int *i, t_data *d);
void		*mini_perror(int err_type, char *param, int err);

/*--- EXECUTER.c ---*/
int			exec_builtin(t_mini *n, t_data *d);
int			child_builtin(t_mini *n, char **env, t_data *d);
int			child_process(t_data *d, t_list *cmd, int fd[2], char **env);
void		*child_redir(t_list *cmd, int fd[2]);
int			exec_fork(t_data *d, t_list *cmd, int fd[2], char **env);

/*--- EXECUTER_2.c ---*/
int			builtin(t_data *d, t_list *cmd, char **env);
void		*exec_cmd(t_data *d, t_list *cmd, char **env);
void		*check_to_fork(t_data *d, t_list *cmd, int fd[2], char **env);
int			check_f_d(t_mini *n);
char		*clean_quotes(char *s);

/*--- LEXER_COPY.c ---*/
void		lexer_2(t_data *d);
int			check_quotes(char *s);

/*--- SIGNAL.c ---*/
void		handler_sigint(int sig);
void		handler_sigquit(int sig);

int			check_f_d(t_mini *n);
int			check_builtin_2(char *s);

#endif
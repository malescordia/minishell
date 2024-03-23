/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:12:52 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/19 17:52:24 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define PURPLE "\033[35m"
# define BLUE "\033[36m"
# define R "\033[0m" /* reset colors */

extern int			g_signal;

typedef struct s_cmds
{
	char			**args;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_data
{
	t_list			**env;
	t_list			**export;
	t_cmds			*cmds;
	int				exit;
	int				nb_of_cmds;
	int				cmd_in_fd;
	int				fd_in;
	int				fd_out;
	char			*input;
	char			**main_input;
}					t_data;

/* main */
int					print_token_message(char token);

/* check_input_1 */
int					check_start(char *input);
int					check_input(t_data *data);
int					check_tokens(char *input);
int					check_dollar(char *input);
int					check_double_redir(char *input);

/* check_input_2 */
int					check_end(char *input);
int					check_pipe(char *input);
int					check_order(char *input);
int					check_redir(char *input);
int					check_quote(char *input);

/* check_cmd */
void				execute(t_data *data, char **cmds);
int					is_exec(t_data *data, char *cmd, char **paths);

/* parse */
int					parse_normal(char *input, int i);
int					parse_others(char *input, int i);
int					parse_env(char *input, int i);
int					parse_quotes(char *input, char quote, int i);

/* quote_utils */
int					get_nb_of_quotes(char *str);
char				*remove_quotes(char *str);
int					ignore_quotes(char *input, int i);

/* split */
int					count_words(char *input);
int					split_words(char *input);
char				**split_input(t_data *data, char *input);
char				*split_alloc(t_data *data, char *input, int len);

/* input_utils */
int					check_char(char c);
int					input_size(char **input);
char				**input_dup(t_data *data, char **old);

/* init */
int					init_data(t_data *data);
t_cmds				*init_cmds(t_data *data);

/* expansion */
char				**expander(t_data *data);
int					get_value_len(char *str);
char				*get_value(t_data *data, char *str);
int					get_index(t_data *data, char *result, char quotes, int i);
char				*substitute_value(t_data *data, char *result, char quotes,
						int i);

/* expansion utils */
char				*value_cmp(char *env, char *value);
char				*value_iter(t_data *data, char *value);
char				*env_grep_value(t_list *env, char *value);

/* free */
int					free_array(char **arr);
void				free_list(t_list **lst);
void				free_cmds(t_cmds *cmds);
void				free_data(t_data *data);
void				free_list_malloc(t_list **list);

/* cmd */
int					get_cmds_nb(char **input);
int					get_args_nb(char **input, int i);
t_cmds				*create_node(t_data *data, int i);
int					find_next_cmd(char **input, int i);

/* tokenize */
char				**tokenizer(t_data *data, char **input, int i);
int					token_expand(t_data *data, char **tmp, char *input, int i);

/* redirection */
void				reset_fds(t_data *data);
int					redir_set(t_data *data, char **main_input, int position,
						int child);
int					redir_out(t_data *data, char *out_file, int append,
						int child);
int					redir_in(t_data *data, char *in_file, int heredoc,
						int child);

/* builtins */
int					is_builtin(char *str);
void				export_builtin(t_data *data, char **cmds);
void				read_builtin(t_data *data, char **cmds, int parent);

/* error_1 */
void				malloc_error(t_data *data);
void				pipe_error(t_data *data, int *pipe_fd);
void				fork_error(t_data *data, int *pipe_fd);
int					export_error_message(t_data *data, char *error);
int					open_error(t_data *data, char *filename, int child);

/* error_2 */
void				heredoc_eof(char *limiter);

/* start */
void				start(t_data *data);
void				parent_exec(t_data *data, int *pipe_fd, int done_cmds,
						int position);
void				child_exec(t_data *data, int *pipe_fd, int done_cmds,
						int position);
void				get_exit_status(t_data *data, int fork_id, int done_cmds);
/* execute */
char				**special_path(const char *cmd);
void				execute(t_data *data, char **cmds);
char				**get_paths(t_list **env, char *cmd);
char				*get_cmd_path(t_data *data, char **paths, char *cmd);

/* utils_1 */
char				**list_to_array(t_list **lst);
void				list_swap(t_data *data, t_list *lst);
int					list_check_dup(t_list **lst, char *str);
void				list_remove(t_list **list, int position);
void				list_sort(t_data *data, t_list **export);

/* utils_2 */
void				list_print(t_list **lst);

/* echo */
int					read_echo(t_data *data, char **cmds);

/* pwd */
void				read_pwd(t_data *data);

/* cd */
void				read_cd(t_data *data, char **path);

/* env */
t_list				**init_env(char **envp);
void				env_override(char *str, t_list **env);

/* export */
char				*export_input(char *input);
t_list				**init_export(t_data *data);
void				read_export(t_data *data, char **input);

/* exit */
void				read_exit(t_data *data, char **cmds, int parent);

/* unset */
void				read_unset(t_data *data, char **cmds);

/* signal_catch */
void				sig_init(void);
void				sig_setup(int signum);
void				signal_stop(int signum);
void				post_process_signal(void);
void				signal_exit(t_data *data);

/* heredoc */
int					heredoc_init(t_data *data, char **input);
char				*read_heredoc(t_data *data, char *limiter, int here_num);
char				*output_heredoc(t_data *data, char *limiter, char *line);
void				child_heredoc(t_data *data, char *filename, char *limiter);

/* heredoc_utils */
void				change_terminal(void);
void				signal_heredoc(int signum);
char				*filename_init(int here_num);
int					create_file(t_data *data, char *filename);

/* TESTERS */
void				print_cmds(t_cmds *cmds);

#endif

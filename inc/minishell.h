/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:12:52 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/27 17:31:45 by gude-cas         ###   ########.fr       */
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

extern int			g_signal;

typedef struct s_cmds
{
	char			**args;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_data
{
	t_cmds			*cmds;
	t_list			**env;
	t_list			**export;
	int				exit;
	int				fd_in;
	int				fd_out;
	int				cmd_in_fd;
	int				nb_of_cmds;
	char			*input;
	char			**main_input;
}					t_data;

t_cmds				*init_cmds(t_data *data);
t_cmds				*create_node(t_data *data, int i);

t_list				**init_env(char **envp);
t_list				**init_export(t_data *data);

void				sig_init(void);
void				change_terminal(void);
void				sig_setup(int signum);
void				read_pwd(t_data *data);
void				start_protocol(t_data *data);
void				signal_stop(int signum);
void				free_list(t_list **lst);
void				free_cmds(t_cmds *cmds);
void				free_data(t_data *data);
void				reset_fds(t_data *data);
void				list_print(t_list **lst);
void				post_process_signal(void);
void				signal_exit(t_data *data);
void				free_heredoc(t_data *data);
void				malloc_error(t_data *data);
void				signal_heredoc(int signum);
void				heredoc_eof(char *limiter);
void				free_list_malloc(t_list **list);
void				check_env(char *str, t_list **env);
void				read_cd(t_data *data, char **path);
void				execute(t_data *data, char **cmds);
void				list_swap(t_data *data, t_list *lst);
void				read_unset(t_data *data, char **cmds);
void				pipe_error(t_data *data, int *pipe_fd);
void				fork_error(t_data *data, int *pipe_fd);
void				read_export(t_data *data, char **input);
void				list_remove(t_list **list, int position);
void				list_sort(t_data *data, t_list **export);
void				export_builtin(t_data *data, char **cmds);
void				read_exit(t_data *data, char **cmds, int parent);
void				read_builtin(t_data *data, char **cmds, int parent);
void				get_exit_status(t_data *data, int fork_id, int done_cmds);
void				child_heredoc(t_data *data, char *filename, char *limiter);
void				child_exec(t_data *data, int *pipe_fd, int done_cmds,
						int position);
void				parent_exec(t_data *data, int *pipe_fd, int done_cmds,
						int position);

int					check_char(char c);
int					is_builtin(char *str);
int					check_end(char *input);
int					free_array(char **arr);
int					check_pipe(char *input);
int					init_data(t_data *data);
int					check_start(char *input);
int					check_order(char *input);
int					input_size(char **input);
int					check_quote(char *input);
int					check_redir(char *input);
int					count_words(char *input);
int					split_words(char *input);
int					check_input(t_data *data);
int					check_tokens(char *input);
int					check_dollar(char *input);
int					get_variable_len(char *str);
int					get_nb_of_quotes(char *str);
int					get_nb_of_cmds(char **input);
int					parse_env(char *input, int i);
int					print_token_message(char token);
int					check_double_redir(char *input);
int					parse_normal(char *input, int i);
int					parse_others(char *input, int i);
int					ignore_quotes(char *input, int i);
int					find_next_cmd(char **input, int i);
int					get_nb_of_args(char **input, int i);
int					read_echo(t_data *data, char **cmds);
int					heredoc_init(t_data *data, char **input);
int					create_file(t_data *data, char *filename);
int					parse_quotes(char *input, char quote, int i);
int					is_exec(t_data *data, char *cmd, char **paths);
int					export_error_message(t_data *data, char *error);
int					open_error(t_data *data, char *filename, int child);
int					get_index(t_data *data, char *result, char quotes, int i);
int					token_expand(t_data *data, char **tmp, char *input, int i);
int					redir_in(t_data *data, char *in_file, int heredoc,
						int child);
int					redir_out(t_data *data, char *out_file, int append,
						int child);
int					redir_set(t_data *data, char **main_input, int position,
						int child);

char				*remove_quotes(char *str);
char				*export_input(char *input);
char				*filename_init(int here_num);
char				*get_value(t_data *data, char *str);
char				*find_value(t_data *data, char *value);
char				*compare_value(char *env, char *value);
char				*env_grep_value(t_list *env, char *value);
char				*split_alloc(t_data *data, char *input, int len);
char				*get_cmd_path(t_data *data, char **paths, char *cmd);
char				*read_heredoc(t_data *data, char *limiter, int here_num);
char				*output_heredoc(t_data *data, char *limiter, char *line);
char				*substitute_value(t_data *data, char *result, char quotes,
						int i);

char				**expander(t_data *data);
char				**special_path(const char *cmd);
char				**get_paths(t_list **env, char *cmd);
char				**input_dup(t_data *data, char **old);
char				**split_input(t_data *data, char *input);
char				**list_to_array(t_data *data, t_list **list);
char				**tokenizer(t_data *data, char **input, int i);

#endif

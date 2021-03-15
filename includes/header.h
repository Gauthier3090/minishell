/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:52:25 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/15 17:02:35 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "define.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <fcntl.h>

typedef struct		s_struct
{
	char			*env;
	char			*oldpwd;
	char			*cd_count;
	int				return_status;
	int				cd_len;
	char			*temp;
	char			*temp2;
	char			*arg;
	int				i;
	int				j;
	int				y;
	int				x;
	int				z;
	int				p;
	int				pipin;
	int				check;
	char			**tab;
	char			**exec;
	char			**semico;
	char			**pipe_tab;
	int				pipe_ite;
	char			*save_old_pwd;
	int				semi[1000];
	int				pipe[1000];
	int				sig;
	pid_t			id1;
	pid_t			id2;
}					t_struct;

typedef struct		s_minishell
{
	char			**env;
	char			**tab;
	char			**backs_tab;
	char			*backs_input;
	char			**pipe_backs_tab;
	char			**semi_backs_tab;
	int				white;
	char			**redir_tab;
	char			*input;
	char			*variable;
	char			*value;
	char			*arg;
	int				i;
	int				index;
	int				index_tab;
	int				ret;
	int				quote;
	int				redir[1000];
	int				redirection_read;
	int				double_right;
	int				double_left;
	char			**pipe_tab;
	int				j;
	int				index_redir;
	int				z;
	int				pipe[1000];
	char			*str;
	int				delete_redir;
}					t_minishell;

/*
** backslash.c
*/
void				ft_backslash_tab(t_minishell *shell);
void				ft_tab_dup(t_minishell *shell, t_struct *glo);
char				*ft_backslash_input(char *str, t_minishell *shell);
int					ft_backs_str_simple(t_minishell *shell, char *str, int i);

/*
** backslash2.c
*/
char				*ft_backs_whitespace(t_minishell *shell, char *str);
char				*ft_backzero(char *str);
int					ft_voided_char_input(int i, t_minishell *shell);
int					ft_voided_char(int i, int x, t_minishell *shell);

/*
** backslash3.c
*/
int					ft_backslash_input_sub(char *str,
					t_minishell *shell, int i);

/*
** cd.c
*/
int					ft_cd(char *input, char **env,
					t_struct *glo, t_minishell *shell);
char				*ft_cd_check(t_minishell *shell, char **env,\
					t_struct *glo, char **arg);
int					ft_cd_error(char *arg, t_minishell *shell);
int					ft_oldpwd(t_struct *glo, t_minishell *shell);

/*
** cd2.c
*/
int					ft_home_dir(t_struct *glo, char **env, t_minishell *shell);
int					ft_tilde(t_minishell *shell, char **env, t_struct *glo);
int					ft_change_dir(char *arg, char **env, t_struct *glo, \
					t_minishell *shell);
int					ft_strhomelen(t_struct *glo);

/*
** echo.c
*/
void				echo(t_minishell *shell);

/*
** env.c
*/
void				ft_env(char **tab, char **env, t_minishell *shell);

/*
** error.c
*/
int					ft_putstr_error(char *message, char *variable, int error);
void				ft_put_errno(int error_numb, t_minishell *shell);

/*
** exec.c
*/
int					ft_exec(t_minishell *minishell, t_struct *glo);
char				*check_dir_bin(char *bin, char *command);
int					ft_fork_exec(t_struct *glo, char **bin, char *path, \
					t_minishell *shell);

/*
** exec2.c
*/
void				ft_free_exec(t_struct *glo, char **bin, \
					char *path, int ret);
int					ft_error_exec(char *path);
int					ft_exec_core(t_struct *glo, t_minishell *shell, char *path);
void				ft_exec_ret(int ret, t_minishell *shell);

/*
** exit.c
*/
int					exit_shell(char **tab, t_minishell *shell);

/*
** export.c
*/
void				export(t_minishell *minishell);
int					variable_exist(char **env, char *str);
void				variable_no_exist(t_minishell *shell, char *variable);

/*
** export2.c
*/
void				sorting_env(char **env, int size);
char				*tabtostr(char **tab, int return_line);

/*
** export3.c
*/
void				exception_export(t_minishell *shell);

/*
** free.c
*/
void				free_tab(char **tab);
int					free_tab_ret(char **tab);
void				ft_free_args(t_minishell *shell);
void				ft_free_redir_arg(t_minishell *shell, char *arg);
void				ft_free_failed(t_minishell *shell, char *arg);

/*
** main.c
*/
int					ft_builtins(t_minishell *minishell, t_struct *glo);
void				loop_prompt(t_minishell *shell, t_struct *glo);
void				ft_loop_main(t_minishell *shell, t_struct *glo);

/*
** parsing.c
*/
char				*parse_input(char *input, t_minishell *shell);

/*
** parsing2.c
*/
char				*str_not_env_double_quotes(char *input, int *i);
char				*str_not_env_simple_quotes(char *input, int *i);
char				*str_not_env(char *input, int *i);
char				*str_env(char *input, int *i, char **env, int ret);

/*
** parsing3.c
*/
char				*found_env_exeception(char *str, int ret);
int					str_env_length(char *input, int *i);
char				*str_not_env_backslash(char *input, int *i);

/*
** pipe.c
*/
int					ft_pipe_main(t_minishell *shell, t_struct *glo);
int					ft_multi_pipe(t_minishell *shell, t_struct *glo);

/*
** pipe2.c
*/
void				ft_next_pipe(t_minishell *shell, t_struct *glo);
int					ft_error_pipe(int error_numb, t_minishell *shell);
int					ft_pipe_loop(t_minishell *shell, t_struct *glo);
int					ft_pipe_sub_more(t_minishell *shell, t_struct *glo,
					int x, int z);

/*
** prompt.c
*/
char				*getinput(void);
void				directoryprompt(void);

/*
** pwd.c
*/
void				ft_pwd(t_minishell *shell);

/*
** redirection.c
*/
int					ft_redirection(t_minishell *shell, t_struct *glo);

/*
** redirection2.c
*/
int					ft_count_redirection(char *str, t_minishell *shell);

/*
** redirection3.c
*/
int					ft_pipe_malloc(t_minishell *shell, char *str);
int					ft_split_pipe(t_minishell *shell, char c);
int					error_redirection(char *error, char *var, int ret,
					t_minishell *shell);

/*
** redirection4.c
*/
int					ft_split_redirection(t_minishell *shell, char *str,
					int c, int c2);

/*
** redirection5.c
*/
int					check_redirection(char *str);
char				*ft_redirection_right(t_minishell *shell, int *i,
					int *k, char *arg);
char				*create_arg(char **redir_tab, char *arg, int i,
					t_minishell *shell);

/*
** redirection6.c
*/
char				*ft_redirection_arg(char **redir_tab, t_minishell *shell);
char				*ft_create_redirection(char *str, t_minishell *shell);
int					ft_check_file(int *k, t_minishell *shell);

/*
** redirection7.c
*/
int					ft_redirection_quotes(t_minishell *shell, int i, int j);
char				*ft_redirection_left(t_minishell *shell, char *arg,
					int *k, int *i);

/*
** redirection8.c
*/
void				ft_redirection_pipe(t_minishell *shell, t_struct *glo);
int					ft_redirection_backslash(t_minishell *shell);
char				*ft_redirection_arg_return(char *arg, char **redir_tab);

/*
** semicolon.c
*/
int					ft_semicolon(t_minishell *minishell, t_struct *glo);
int					ft_check_double_char(t_minishell *minishell,
					t_struct *glo, char c);
int					ft_semicolon_sub(t_minishell *minishell, t_struct *glo);

/*
** semicolon2.c
*/
void				ft_check_double_char_sub(t_minishell *shell, t_struct *glo);
void				ft_semico_malloc(t_minishell *shell, t_struct *glo);

/*
** split.c
*/
char				**split_input(char *str);

/*
** signal.c
*/
int					ft_signal_hand(void);
void				sigint_handler(int nothing);
void				sigint_handler2(int nothing);
void				do_nothing(int nothing);
int					ft_signal_hand2(void);

/*
** split2.c
*/
int					count_words(char *str);
void				size_words_null_quotes(char *str, int *i, int *size);

/*
** unset.c
*/
void				unset(t_minishell *shell);
char				**delete_env(t_minishell *shell, int index);

/*
** utility.c
*/
void				save_env(char *tab, char **env, t_struct *glo);
int					ft_strisdigit(char *str);
int					ft_strlen_tab(char **tab);
char				*ft_whitespace(char *input, t_minishell *shell);

/*
** utility2.c
*/
char				*ft_strcat(char *dest, char *src);
void				ft_print_tab(char **tab);
void				*ft_realloc(void *ptr, size_t size);
char				*ft_strcpy(char *dest, char *src);
int					ft_strcmp(const char *s1, const char *s2);

/*
** utility3.c
*/
char				*delete_char_left(char *str, char c);
char				*delete_char_right(char *str, char c);

/*
** utility4.c
*/
char				*path_join(const char *s1, const char *s2);
int					check_quotes_close(char *str);
char				*realloc_str(char *dest, char *src);
void				ft_close_fd(t_struct *glo, int *pipefd, t_minishell *shell);

/*
** utility5.c
*/
int					ft_simple_quotes_check(char *str, int var,
					t_minishell *shell);
int					ft_double_quotes_check(char *str, int var,
					t_minishell *shell);
int					ft_struct_init(t_struct *glo, t_minishell *shell);
char				**malloc_tab(char **tab);

/*
** utility6.c
*/
void				ft_free_exec(t_struct *glo, char **bin, \
					char *path, int ret);
int					ft_error_exec(char *path);
int					ft_exec_core(t_struct *glo, t_minishell *shell, char *path);
void				ft_exec_ret(int ret, t_minishell *shell);
char				*empty_input(char *final_str);

/*
** utility7.c
*/
void				init_shell_arg(t_minishell *shell);
int					ft_builtins(t_minishell *shell, t_struct *glo);
char				*check_backslash_quote(char *input, int i,
					t_minishell *shell);
int					ft_quotes_check_sub_double(char *str, int i,
					int var, t_minishell *shell);

/*
** utility8.c
*/
void				init_shell_arg(t_minishell *shell);
int					ft_builtins(t_minishell *shell, t_struct *glo);
int					ft_no_path(t_minishell *shell, t_struct *glo);
int					free_tab_ret_neg(char **tab);

#endif

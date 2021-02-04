/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:52:25 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/04 17:13:29 by ldavids          ###   ########.fr       */
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
	int				semi[100];
	int				pipe[100];
	pid_t			id1;
	pid_t			id2;
}					t_struct;

typedef struct		s_minishell
{
	char			**env;
	char			**tab;
	char			*input;
	char			*variable;
	char			*value;
	char			*arg;
	int				i;
	int				ret;
	int				quote;
}					t_minishell;

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
** exec.c
*/
int					ft_exec(t_minishell *minishell, t_struct *glo);
char				*check_dir_bin(char *bin, char *command);
int					ft_fork_exec(t_struct *glo, char **bin, char *path, \
					t_minishell *shell);

/*
** exit.c
*/
void				exit_shell(char **tab, int ret);

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
char				*tabtostr(char **tab);

/*
** free.c
*/
void				free_tab(char **tab);
int					free_tab_ret(char **tab);
void				ft_free_exec(t_struct *glo, char **bin, char *path);
void				ft_free_args(t_minishell *shell);

/*
** main.c
*/
void				ft_builtins(t_minishell *minishell, t_struct *glo);
void				ft_loop_main(t_minishell *shell, t_struct *glo);

/*
** parsing.c
*/
char				*parse_input(char *input, char **env, int ret);

/*
** parsing2.c
*/
char				*str_not_env_double_quotes(char *input, int *i);
char				*str_not_env(char *input, int *i);
char				*str_env(char *input, int *i, char **env, int ret);

/*
** pipe.c
*/
int					ft_pipe_main(t_minishell *shell, t_struct *glo);

/*
** pipe2.c
*/
void				ft_next_pipe(t_minishell *shell, t_struct *glo);
int					ft_error_pipe(int error_numb, t_minishell *shell);
int					ft_pipe_loop(t_minishell *shell, t_struct *glo);

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
int					ft_redirection(t_minishell *shell);

/*
** semicolon.c
*/
int					ft_semicolon(t_minishell *minishell, t_struct *glo);
int					ft_check_double_char(t_minishell *minishell,
					t_struct *glo, char c);
int					ft_semicolon_sub(t_minishell *minishell, t_struct *glo);
int					ft_double_quotes_check(t_minishell *shell, int var);

/*
** semicolon2.c
*/
void		ft_check_double_char_sub(t_minishell *shell, t_struct *glo);
void		ft_semico_malloc(t_minishell *shell, t_struct *glo);

/*
** utility5.c
*/
void		ft_signal_hand();

/*
** split.c
*/
char				**split_input(char *str);

/*
** split2.c
*/
int					count_words(char *str);

/*
** unset.c
*/
void				unset(t_minishell *shell);
char				**delete_env(t_minishell *shell, int index);

/*
** utility.c
*/
int					ft_struct_init(t_struct *glo, t_minishell *shell);
void				save_env(char *tab, char **env, t_struct *glo);
int					ft_strisdigit(char *str);
int					ft_strlen_tab(char **tab);
char				*ft_whitespace(char *input);

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
void				ft_put_errno(int error_numb, t_minishell *shell);
int					ft_putstr_error(char *message, char *variable, int error);
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
int		ft_quotes_check_sub(t_minishell *shell, int i, int var, char c);
int		ft_simple_quotes_check(t_minishell *shell, int var);
int		ft_double_quotes_check(t_minishell *shell, int var);
int		ft_struct_init(t_struct *glo, t_minishell *shell);

#endif

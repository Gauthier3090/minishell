/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:52:25 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/05 15:44:21 by gpladet          ###   ########.fr       */
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
	int				y;
	int				x;
	int				check;
	char			**tab;
	char			**tab2;
	char			**forked_tab;
	pid_t			id1;
	pid_t			id2;
}					t_struct;

typedef struct		s_minishell
{
	char			**env;
	char			**tab;
	char			**tab_input;
	char			*input;
	char			*variable;
	char			*tmp_variable;
	char			*value;
	int				simple_quote;
	int				simple_quote_left;
	int				simple_quote_right;
	int				double_quote;
	int				double_quote_left;
	int				double_quote_right;
	int				len;
	int				count;
	int				i;
	int				quote;
	int				go_free;
	int				free_var;
}					t_minishell;

void				directoryprompt();
void				ft_builtins(t_minishell *minishell, t_struct *glo);
int					ft_struct_init(t_struct *glo);
void				echo(t_minishell *shell);
char				*delete_char_left(char *str, char c);
char				*delete_char_right(char *str, char c);
void				echo_env(char *tab, char **env);
void				save_env(char *tab, char **env, t_struct *glo);
void				free_tab(char **tab);
void				free_var_unset(char **arg, char *value, char *str, char *tmp);
void				*ft_realloc(void *ptr, size_t size);
char				*getdirectory(void);
char				*getinput(void);
int					ft_cd(char *input, char **env, t_struct *glo);
char				*ft_whitespace(char *input);
int					ft_absolute_path(char *arg, t_struct *glo);
char				*ft_cd_args_check(char **arg, char **env, t_struct *glo);
int					ft_strlen_tab(char **tab);
int					ft_strisdigit(char *str);
void				exit_shell(char **tab);
void				ft_env(char **tab, char **env);
int					ft_change_dir(char *arg, char **env,
					t_struct *glo, char **tab);
int					ft_oldpwd(t_struct *glo, char **arg);
int					ft_cd_error(char *arg);
void				export(t_minishell *minishell);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, char *src);
void				ft_print_tab(char **tab);
int					ft_strhomelen(t_struct *glo);
int					ft_home_dir(t_struct *glo, char **env, char **arg);
int					free_tab_ret(char **tab);
int					ft_tilde(char **arg, char **env, t_struct *glo);
char				*ft_cd_env(char **arg, char **env, t_struct *glo);
void				ft_path_len(char *arg, t_struct *glo);
char				*ft_strcat(char *dest, char *src);
void				sorting_env(char **env, int size);
char				*tabtostr(char **tab);
char				*ft_cd_env_sub(char *arg, char **env, t_struct *glo);
void				ft_pwd(char *input);
void				ft_ls(char *input);
void				ft_ls_sub(struct dirent	*entry);
void				ft_errno_putstr(int errnumb);
void				ft_ls_files(void);
void				ft_putstr_error(char *message, char *variable);
int					ft_exec(t_minishell *minishell, t_struct *glo);
char				**ft_exec_env(char **arg, char **env, t_struct *glo);
int					ft_check_tabs(t_minishell *minishell, t_struct *glo);
char				*export_variable(char *str, char **env);
char				*export_variable_env(char *variable, char **arg,
					char **env);
int					export_error(char *variable);
void				export_more(t_minishell *shell, char *variable, char *value);
char				*ft_export(char *variable, char *value, char **env);
int					variable_exist(char **env, char *str);
int					ft_fork_exec(t_struct *glo);
char				*export_variable_start(char *str, int *i);
void				unset(t_minishell *shell);
int					ft_semicolon(t_minishell *minishell, t_struct *glo);
int					ft_semicolon_sub(t_minishell *minishell, t_struct *glo);
int					check_fork(int id, t_struct *glo);
char				*export_value_more(char *value, char *str, int *i);
void				research_env_more(char *variable, t_minishell *shell);
char				*unset_value(char *str, char **env);
int					check_error_unset(char *variable, char *value);
char				**delete_env(t_minishell *shell, int index);
char				*parse_input(t_minishell *shell, char *input, int free_input);
int					length_input(char *str);
char				**input_to_tab(char *str, int length, t_minishell *shell);
int					check_quote_close(t_minishell *shell);
void				is_quote(char *input, t_minishell *shell);
char				*add_quote(char *str, char c);
char				*str_double_quote(t_minishell *shell, int i);
char				*str_simple_quote(t_minishell *shell, int i);
char				*ft_strdel(char *str, char c);
char				*env_start(char *input, int *i);
char				*env_end(char *input, char **arg, char **env);

#endif

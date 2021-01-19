/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:52:25 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/19 14:32:42 by ldavids          ###   ########.fr       */
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
	int				z;
	int				p;
	int				pipin;
	int				check;
	char			**tab;
	char			**tab2;
	char			**forked_tab;
	char			**pipe_tab;
	int				pipe_ite;
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
	int				i;
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
int					ft_cd(char *input, char **env, t_struct *glo, t_minishell *shell);
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
void				ft_pwd(t_minishell * shell);
void				ft_ls(char *input);
void				ft_ls_sub(struct dirent	*entry);
void				ft_errno_putstr(int errnumb);
void				ft_ls_files(void);
void				ft_putstr_error(char *message, char *variable);
int					ft_exec(t_minishell *minishell, t_struct *glo);
char				*check_dir_bin(char *bin, char *command);
char				*export_variable(char *str, char **env);
char				*export_variable_env(char *variable, char **arg,
					char **env);
int					export_error(char *variable);
void				export_more(t_minishell *shell, char *variable, char *value);
char				*ft_export(char *variable, char *value, char **env);
int					variable_exist(char **env, char *str);
int					ft_fork_exec(t_struct *glo, char **bin, char *path);
void				variable_no_exist(t_minishell *shell, char *variable);
char				*export_variable_start(char *str, int *i);
void				unset(t_minishell *shell);
int					ft_semicolon(t_minishell *minishell, t_struct *glo);
int					ft_semicolon_sub(t_minishell *minishell, t_struct *glo);
int					ft_check_double_char(t_minishell *minishell, t_struct *glo, char c);
char				*export_value_more(char *value, char *str, int *i);
void				research_env_more(char *variable, t_minishell *shell);
char				*unset_value(char *str, char **env);
int					check_error_unset(char *variable, char *value);
void				ft_put_errno(int error_numb);
char				**delete_env(t_minishell *shell, int index);
char				*parse_input(char *input, char **env);
int					length_input(char *str);
char				**input_to_tab(char *str, int length, t_minishell *shell);
void				is_quote(char *input, t_minishell *shell);
char				*add_quote(char *str, char c);
char				*str_double_quote(t_minishell *shell, int i);
char				*str_simple_quote(t_minishell *shell, int i);
char				*ft_strdel(char *str, char c);
char				*env_start(char *input, int *i);
char				*env_end(char *input, char **arg, char **env);
char				*path_join(const char *s1, const char *s2);
void				ft_loop_main(t_minishell *shell, t_struct *glo);
char				**split_input(char *str);
int					check_quotes_close(char *str);
char				*realloc_str(char *dest, char *src);
char				*found_env(char *str, char **env);
char				*parse_null_quote(char *input, int *i, char **env);
char				*str_env(char *input, int *i, char **env);
char				*str_not_env(char *input, int *i);
int					ft_pipe_main(t_minishell *shell, t_struct *glo);
void				ft_close_fd(t_struct *glo, int *pipefd);
void				ft_next_pipe(t_minishell *shell, t_struct *glo);
int					ft_error_pipe(int error_numb);

#endif

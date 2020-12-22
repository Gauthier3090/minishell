/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:52:25 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/22 15:40:00 by gpladet          ###   ########.fr       */
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
}					t_struct;

typedef struct		s_minishell
{
	char			**env;
	char			**tab;
	char			*input;
	int				is_active;
}					t_minishell;

void	directoryprompt();
int		ft_struct_init(t_struct *glo);
void	echo(char **tab, char **env);
char	*delete_char_left(char *str, char c);
char	*delete_char_right(char *str, char c);
void	echo_env(char *tab, char **env);
void	save_env(char *tab, char **env, t_struct *glo);
void	free_tab(char **tab);
void	*ft_realloc(void *ptr, size_t size);
char	*getdirectory(void);
char	*getinput(void);
int		ft_cd(char* input, char **env, t_struct *glo);
char*	ft_whitespace(char *input);
int		ft_absolute_path(char *arg, t_struct *glo);
char	*ft_cd_args_check(char **arg, char **env, t_struct *glo);
int		ft_strlen_tab(char **tab);
int		ft_strisdigit(char *str);
void	exit_shell(char **tab);
void	ft_env(char **tab, char **env);
int		ft_change_dir(char *arg, char **env, t_struct *glo, char **tab);
int		ft_oldpwd(t_struct *glo, char **arg);
int		ft_cd_error(char *arg);
void	export(t_minishell *minishell);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, char *src);
void	ft_print_tab(char **tab);
int		ft_strhomelen(t_struct *glo);
int		ft_home_dir(t_struct *glo, char **env, char **arg);
int		free_tab_ret(char **tab);
int		ft_tilde(char **arg, char **env, t_struct *glo);
char	*ft_cd_env(char **arg, char **env, t_struct *glo);
void	ft_path_len(char *arg, t_struct *glo);
char	*ft_strcat(char *dest, char *src);
void	sorting_env(char **env, int size);
char	*tabtostr(char **tab);
char	*ft_cd_env_sub(char *arg, char **env, t_struct *glo);
void	ft_pwd(char *input);
void	ft_ls(char *input);
void	ft_errno_putstr(int errnumb);
void	ft_ls_files(void);
int		ft_exec(t_minishell *minishell);
void	ft_putstr_error(char *message, char *variable);

#endif

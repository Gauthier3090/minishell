/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:52:25 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/07 18:45:33 by gpladet          ###   ########.fr       */
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

void	directoryprompt();
void	echo(char **tab, char **env);
void	free_tab(char **tab);
void	*ft_realloc(void *ptr, size_t size);
char	*getdirectory(void);
char	*getinput(void);
void	ft_cd(char* input);
char*	ft_whitespace(char *input);
int		ft_absolute_path(char *arg);
int		ft_cd_args_check(char **arg);

#endif

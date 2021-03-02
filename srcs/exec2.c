/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:45:59 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/02 15:11:10 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		ft_free_exec(t_struct *glo, char **bin, char *path, int ret)
{
	glo->exec ? free_tab(glo->exec) : 0;
	bin ? free_tab(bin) : 0;
	path ? free(path) : 0;
	if (glo->pipin == 1)
		exit(EXIT_SUCCESS);
	if (ret >= 0)
		exit(ret);
}

int			ft_error_exec(char *path)
{
	DIR	*dir;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && dir == NULL)
		ret = ft_putstr_error(": No such file or directory", NULL, 2);
	else if (fd == -1 && dir != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && dir == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && dir == NULL))
		ret = 127;
	else
		ret = 2;
	if (dir)
		closedir(dir);
	if (fd > -1)
		close(fd);
	return (ret);
}

int			ft_exec_core(t_struct *glo, t_minishell *shell, char *path)
{
	int		ret;

	ret = 0;
	if (path != NULL)
	{
		execve(path, glo->exec, shell->env);
		ret = ft_error_exec(path);
	}
	else
	{
		execve(glo->exec[0], glo->exec, shell->env);
		ret = ft_error_exec(glo->exec[0]);
	}
	return (ret);
}

void		ft_exec_ret(int ret, t_minishell *shell)
{
	if (ret != 0)
		shell->ret = 1;
	if (ret == 512)
		shell->ret = 2;
	if (ret == 32512)
		shell->ret = 127;
	if (ret == 130)
		shell->ret = 130;
	if (ret == 0)
		shell->ret = 0;
}

char		*empty_input(char *final_str)
{
	if (!final_str)
	{
		if (!(final_str = ft_strdup("")))
			exit(EXIT_FAILURE);
	}
	return (final_str);
}

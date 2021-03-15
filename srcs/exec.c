/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:42:42 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/15 16:32:59 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		ft_cmd_not_found(int err_nmb, t_minishell *shell)
{
	if (err_nmb != 2)
		ft_put_errno(err_nmb, shell);
	else
	{
		shell->ret = ft_putstr_error("minishell: command not found ",
		shell->tab[0], 127);
		exit(127);
	}
}

int			ft_fork_exec(t_struct *glo, char **bin, char *path, \
			t_minishell *shell)
{
	int				id;
	int				ret;

	id = fork();
	if (id == -1)
	{
		ft_put_errno(errno, shell);
		free_tab(glo->exec);
		return (1);
	}
	if (id != 0)
	{
		signal(SIGINT, sigint_handler2);
		if (waitpid(id, &ret, 0) == -1)
			ft_put_errno(errno, shell);
		free_tab(glo->exec);
		free_tab(bin);
		free(path);
		ft_exec_ret(ret, shell);
		return (1);
	}
	return (0);
}

char		*check_dir_bin(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

int			ft_exec_sub(t_minishell *shell, t_struct *glo)
{
	int				i;

	i = 0;
	while (shell->tab[i])
		i++;
	if (!(glo->exec = ft_calloc(sizeof(char *), i + 3)))
		exit(EXIT_FAILURE);
	i = 0;
	while (shell->tab[i])
	{
		glo->exec[i] = parse_input(shell->tab[i], shell);
		i++;
	}
	i = 0;
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	if (shell->env[i - 1] && ft_strncmp(shell->env[i - 1], "PATH=", 5) != 0)
		return (-1);
	return (i);
}

int			ft_exec(t_minishell *shell, t_struct *glo)
{
	int				i;
	char			**bin;
	char			*path;
	int				ret;

	if (shell->i > 1)
		return (1);
	glo->i = 0;
	i = ft_exec_sub(shell, glo);
	if (i == -1)
		return (ft_no_path(shell, glo));
	if (!(bin = ft_split(shell->env[i], ':')))
		exit(EXIT_FAILURE);
	i = 1;
	path = check_dir_bin(bin[0] + 5, glo->exec[0]);
	while (glo->exec[0] && bin[i] && path == NULL)
		path = check_dir_bin(bin[i++], glo->exec[0]);
	if (ft_fork_exec(glo, bin, path, shell) == 1)
		return (1);
	ret = ft_exec_core(glo, shell, path);
	ft_free_exec(glo, bin, path, ret);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:42:42 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/27 15:28:55 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		ft_cmn_not_found(int err_nmb, t_minishell *shell)
{
	if (err_nmb != 2)
		ft_put_errno(err_nmb);
	else
	{
		shell->ret = ft_putstr_error("minishell: command not found ",
		shell->tab[0], 127);
		exit(EXIT_SUCCESS);
	}
}

int			ft_fork_exec(t_struct *glo, char **bin, char *path)
{
	int				id;

	id = fork();
	if (id == -1)
	{
		ft_put_errno(errno);
		free_tab(glo->tab2);
		return (1);
	}
	if (id != 0)
	{
		if (wait(NULL) == -1)
			ft_put_errno(errno);
		free_tab(glo->tab2);
		free_tab(bin);
		free(path);
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
	char			*temp;

	i = 0;
	ft_putstr_fd("check", 1);
	while (shell->tab[i])
		i++;
	if (!(glo->tab2 = ft_calloc(sizeof(char *), i + 3)))
		exit(EXIT_FAILURE);
	i = 0;
	while (shell->tab[i])
	{
		temp = delete_char_left(shell->tab[i], '=');
		glo->tab2[i] = parse_input(temp, shell->env, shell->ret);
		free(temp);
		i++;
	}
	i = 0;
	while (shell->env && shell->env[i] && ft_strncmp(\
		shell->env[i], "PATH=", 5) != 0)
		i++;
	return (i);
}

int			ft_exec(t_minishell *shell, t_struct *glo)
{
	int				i;
	char			**bin;
	char			*path;

	if (shell->i > 1)
		return (1);
	glo->i = 0;
	i = ft_exec_sub(shell, glo);
	bin = ft_split(shell->env[i], ':');
	i = 0;
	path = check_dir_bin(bin[0] + 5, glo->tab2[0]);
	while (glo->tab2[0] && bin[i] && path == NULL)
		path = check_dir_bin(bin[i++], glo->tab2[0]);
	if (ft_fork_exec(glo, bin, path) == 1)
		return (1);
	if (path != NULL)
	{
		if (execve(path, glo->tab2, shell->env) == -1)
			ft_put_errno(errno);
	}
	else if (execve(glo->tab2[0], glo->tab2, shell->env) == -1)
		ft_cmn_not_found(errno, shell);
	ft_free_exec(glo, bin, path);
	return (1);
}

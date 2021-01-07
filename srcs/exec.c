/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:42:42 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/07 16:51:01 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int			ft_fork_exec(t_struct *glo, char **bin, char *path)
{
	int				id;

	id = fork();
	if (id == -1)
	{
		ft_put_errno(errno);
		free_tab(glo->tab);
		free_tab(glo->tab2);
		return (1);
	}
	if (id != 0)
	{
		if (wait(NULL) == -1)
			ft_put_errno(errno);
		free_tab(glo->tab);
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

char		**ft_exec_env(char **tab, char **env, t_struct *glo)
{
	int				j;

	j = 0;
	while (tab[j])
	{
		glo->i = 0;
		while (tab[j][glo->i])
		{
			if (tab[j][glo->i] == '$')
			{
				glo->y = glo->i;
				while (tab[j][glo->y] && tab[j][glo->y] != '/')
					glo->y++;
				tab[j] = ft_cd_env_sub(tab[j], env, glo);
			}
			glo->i++;
		}
		j++;
	}
	return (tab);
}

int			ft_exec_sub(t_minishell *minishell, t_struct *glo)
{
	int				i;

	i = 0;
	if (!(glo->tab = ft_split(minishell->input, ' ')))
		exit(EXIT_FAILURE);
	while (glo->tab[glo->i])
		glo->i++;
	glo->tab = ft_exec_env(glo->tab, minishell->env, glo);
	if (!(glo->tab2 = ft_calloc(sizeof(char *), glo->i + 3)))
		exit(EXIT_FAILURE);
	if (!(glo->tab2[0] = ft_strdup(glo->tab[0])))
		exit(EXIT_FAILURE);
	glo->i = 1;
	while (glo->tab[glo->i])
	{
		if (!(glo->tab2[glo->i] = ft_strdup(glo->tab[glo->i])))
			exit(EXIT_FAILURE);
		glo->i++;
	}
	glo->tab2[++glo->i] = NULL;
	while (minishell->env && minishell->env[i] && ft_strncmp(\
		minishell->env[i], "PATH=", 5) != 0)
		i++;
	return (i);
}

int			ft_exec(t_minishell *minishell, t_struct *glo)
{
	int				i;
	char			**bin;
	char			*path;

	glo->i = 0;
	i = ft_exec_sub(minishell, glo);
	bin = ft_split(minishell->env[i], ':');
	i = 0;
	path = check_dir_bin(bin[0] + 5, glo->tab2[0]);
	while (glo->tab2[0] && bin[i] && path == NULL)
		path = check_dir_bin(bin[i++], glo->tab2[0]);
	if (ft_fork_exec(glo, bin, path) == 1)
		return (1);
	if (path != NULL)
	{
		if (execve(path, glo->tab2, minishell->env) == -1)
			ft_put_errno(errno);
	}
	else if (execve(glo->tab2[0], glo->tab2, minishell->env) == -1)
		ft_put_errno(errno);
	free_tab(glo->tab);
	free_tab(glo->tab2);
	free_tab(bin);
	free(path);
	return (1);
}

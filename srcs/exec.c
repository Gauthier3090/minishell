/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:42:42 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/23 16:55:35 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_exec(t_minishell *minishell, t_struct *glo)
{
	glo->i = 0;
	if (ft_check_tabs(minishell, glo) == 0)
		return (0);
	glo->i = 1;
	while (glo->tab[glo->i])
	{
		if (!(glo->tab2[glo->i] = ft_strdup(glo->tab[glo->i])))
			exit(EXIT_FAILURE);
		glo->i++;
	}
	glo->tab2[++glo->i] = NULL;
	if (ft_fork_exec(glo) == 1)
		return (1);
	if (execve(glo->tab2[0], glo->tab2, minishell->env) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	free_tab(glo->tab);
	free_tab(glo->tab2);
	return (1);
}

char	**ft_exec_env(char **tab, char **env, t_struct *glo)
{
	int	j;

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

int		ft_check_tabs(t_minishell *minishell, t_struct *glo)
{
	if (!(glo->tab = ft_split(minishell->input, ' ')))
		exit(EXIT_FAILURE);
	while (glo->tab[glo->i])
		glo->i++;
	glo->tab = ft_exec_env(glo->tab, minishell->env, glo);
	if (!(glo->tab2 = ft_calloc(sizeof(char *), glo->i + 3)))
		exit(EXIT_FAILURE);
	if ((ft_strcmp(glo->tab[0], "bash") == 0) || \
	(ft_strcmp(glo->tab[0], "sh") == 0))
	{
		if (!(glo->tab2[0] = ft_strdup("/bin/bash")))
			exit(EXIT_FAILURE);
	}
	else if ((ft_strncmp(glo->tab[0], "./", 2) == 0) || (glo->tab[0][0] == '/'))
	{
		if (!(glo->tab2[0] = ft_strdup(glo->tab[0])))
			exit(EXIT_FAILURE);
	}
	else
	{
		free_tab(glo->tab);
		free_tab(glo->tab2);
		return (0);
	}
	return (1);
}

int		ft_fork_exec(t_struct *glo)
{
	int		id;

	id = fork();
	if (id == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
		free_tab(glo->tab);
		free_tab(glo->tab2);
		return (1);
	}
	if (id != 0)
	{
		if (wait(NULL) == -1)
		{
			ft_putstr_fd(strerror(errno), 1);
			write(1, "\n", 1);
		}
		free_tab(glo->tab);
		free_tab(glo->tab2);
		return (1);
	}
	return (0);
}

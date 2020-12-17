/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:38:20 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/16 16:46:56 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_cd_env_sub(char *arg, char **env, t_struct *glo)
{
	if (!(glo->temp = ft_substr(arg, glo->i, glo->y)))
		exit(EXIT_FAILURE);
	save_env(glo->temp, env, glo);
	free(glo->temp);
	if (ft_strncmp(glo->env, " ", ft_strlen(glo->env)) != 0)
	{
		if (!(glo->temp = ft_substr(arg, 0, glo->i)))
			exit(EXIT_FAILURE);
		if (!(glo->temp2 = ft_strjoin(glo->temp, glo->env)))
			exit(EXIT_FAILURE);
		free(glo->temp);
		if (!(glo->temp = ft_substr(arg, glo->y, ft_strlen(arg) - glo->y)))
			exit(EXIT_FAILURE);
		free(arg);
		if (!(arg = ft_strjoin(glo->temp2, glo->temp)))
			exit(EXIT_FAILURE);
		free(glo->temp2);
		free(glo->temp);
		return (arg);
	}
	free(arg);
	if (!(arg = ft_strdup(" ")))
		exit(EXIT_FAILURE);
	return (arg);
}

int		ft_tilde(char **arg, char **env, t_struct *glo)
{
	char	*temp;

	temp = ft_substr(arg[0], 1, ft_strlen(arg[0]));
	save_env("$HOME", env, glo);
	free(arg[0]);
	arg[0] = ft_strjoin(glo->env, temp);
	free(temp);
	return (TRUE);
}

int		ft_change_dir(char *arg, char **env, t_struct *glo, char **tab)
{
	save_env("$HOME", env, glo);
	ft_strhomelen(glo);
	if (ft_strncmp(arg, "..", 3) == 0 && ft_strncmp(glo->oldpwd, \
		glo->env, glo->cd_len + 1) == 0)
	{
		glo->cd_count++;
		free_tab(tab);
		return (TRUE);
	}
	if (chdir(arg) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	glo->cd_count++;
	free_tab(tab);
	return (TRUE);
}

int		ft_strhomelen(t_struct *glo)
{
	char	*temp;

	glo->cd_len = 1;
	while (glo->env[glo->cd_len] != '/')
		glo->cd_len++;
	if (!(temp = ft_strdup(glo->env)))
		exit(EXIT_FAILURE);
	free(glo->env);
	if (!(glo->env = ft_substr(temp, 0, glo->cd_len)))
		exit(EXIT_FAILURE);
	free(temp);
	return (TRUE);
}

int		ft_home_dir(t_struct *glo, char **env, char **arg)
{
	save_env("$HOME", env, glo);
	if (chdir(glo->env) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	glo->cd_count++;
	free_tab(arg);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:38:20 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/15 18:02:55 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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
	if (ft_strhomelen(glo) == FALSE)
		return (FALSE);
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
		return (FALSE);
	free(glo->env);
	if (!(glo->env = ft_substr(temp, 0, glo->cd_len)))
		return (FALSE);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:38:20 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/23 17:12:22 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_tilde(t_minishell *shell, char **env, t_struct *glo)
{
	char	*temp;

	temp = ft_substr(shell->variable, 1, ft_strlen(shell->variable));
	save_env("$HOME", env, glo);
	free(shell->variable);
	shell->variable = ft_strjoin(glo->env, temp);
	free(temp);
	return (TRUE);
}

int		ft_change_dir(char *variable, char **env, t_struct *glo)
{
	save_env("$HOME", env, glo);
	ft_strhomelen(glo);
	if (ft_strncmp(variable, "..", 3) == 0 && ft_strncmp(glo->oldpwd, \
		glo->env, glo->cd_len + 1) == 0)
	{
		glo->cd_count++;
		return (TRUE);
	}
	if (chdir(variable) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		glo->cd_count = 0;
		write(1, "\n", 1);
		free(glo->oldpwd);
		glo->oldpwd = ft_strdup(glo->save_old_pwd);
	}
	glo->cd_count++;
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

int		ft_home_dir(t_struct *glo, char **env)
{
	save_env("$HOME", env, glo);
	if (chdir(glo->env) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
		glo->cd_count = 0;
	}
	glo->cd_count++;
	return (TRUE);
}

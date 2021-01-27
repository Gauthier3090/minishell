/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:55 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/27 15:54:16 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_oldpwd(t_struct *glo)
{
	char		*buf;

	if ((buf = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd(strerror(errno), 1);
		free(buf);
		return (FALSE);
	}
	if (glo->cd_count == 0)
	{
		ft_putstr_fd("OLDPWD not set\n", 1);
		free(buf);
		return (FALSE);
	}
	ft_cd_error(glo->oldpwd);
	ft_putstr_fd(glo->oldpwd, 1);
	write(1, "\n", 1);
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(buf)))
		exit(EXIT_FAILURE);
	glo->cd_count++;
	free(buf);
	return (TRUE);
}

int		ft_cd_error(char *variable)
{
	if (chdir(variable) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	return (TRUE);
}

char	*ft_cd_check(t_minishell *shell, char **env, t_struct *glo, char **arg)
{
	if (arg[1])
	{
		ft_putstr_fd("too many arguments", 1);
		write(1, "\n", 1);
		glo->i = FALSE;
		free_tab(arg);
		return (shell->variable);
	}
	free_tab(arg);
	if (shell->variable[0] == '~')
	{
		if (!(ft_tilde(shell, env, glo)))
			exit(EXIT_FAILURE);
	}
	glo->i = TRUE;
	free(glo->save_old_pwd);
	glo->save_old_pwd = ft_strdup(glo->oldpwd);
	return (shell->variable);
}

int		ft_cd(char *input, char **env, t_struct *glo, t_minishell *shell)
{
	char	**arg;

	if (shell->i > 1)
		return (0);
	if (!(glo->temp = ft_substr(input, 2, ft_strlen(input))))
		exit(EXIT_FAILURE);
	if (!(arg = ft_split(glo->temp, ' ')))
		exit(EXIT_FAILURE);
	free(glo->temp);
	if (shell->variable == NULL)
	{
		free_tab(arg);
		return (ft_home_dir(glo, env));
	}
	shell->variable = ft_cd_check(shell, env, glo, arg);
	if (glo->i == FALSE)
		return (FALSE);
	if (ft_strncmp(shell->variable, "-", 2) == 0)
		return (ft_oldpwd(glo));
	free(glo->oldpwd);
	if (!(glo->oldpwd = getcwd(NULL, 0)))
		return (FALSE);
	if (ft_strncmp(shell->variable, "--", 3) == 0)
		return (ft_home_dir(glo, env));
	return (ft_change_dir(shell->variable, env, glo));
}

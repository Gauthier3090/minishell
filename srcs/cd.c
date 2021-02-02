/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:55 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/02 21:49:30 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_oldpwd(t_struct *glo, t_minishell *shell)
{
	char		*buf;

	if ((buf = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd(strerror(errno), 2);
		shell->ret = 1;
		free(buf);
		return (FALSE);
	}
	if (glo->cd_count == 0)
	{
		shell->ret = ft_putstr_error("OLDPWD not set\n", NULL, 1);
		free(buf);
		return (FALSE);
	}
	ft_cd_error(glo->oldpwd, shell);
	ft_putstr_fd(glo->oldpwd, 1);
	write(1, "\n", 1);
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(buf)))
		exit(EXIT_FAILURE);
	glo->cd_count++;
	free(buf);
	return (TRUE);
}

int		ft_cd_error(char *variable, t_minishell *shell)
{
	if (chdir(variable) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		shell->ret = 1;
	}
	return (TRUE);
}

char	*ft_cd_check(t_minishell *shell, char **env, t_struct *glo, char **arg)
{
	if (arg[1])
	{
		shell->ret = ft_putstr_error("too many arguments\n", NULL, 1);
		glo->i = FALSE;
		free_tab(arg);
		return (shell->arg);
	}
	free_tab(arg);
	if (shell->arg[0] == '~')
	{
		if (!(ft_tilde(shell, env, glo)))
			exit(EXIT_FAILURE);
	}
	glo->i = TRUE;
	free(glo->save_old_pwd);
	if (!(glo->save_old_pwd = ft_strdup(glo->oldpwd)))
		exit(EXIT_FAILURE);
	return (shell->arg);
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
	if (shell->arg == NULL)
	{
		free_tab(arg);
		return (ft_home_dir(glo, env, shell));
	}
	shell->arg = ft_cd_check(shell, env, glo, arg);
	if (glo->i == FALSE)
		return (FALSE);
	if (ft_strncmp(shell->arg, "-", 2) == 0)
		return (ft_oldpwd(glo, shell));
	free(glo->oldpwd);
	if (!(glo->oldpwd = getcwd(NULL, 0)))
		return (FALSE);
	if (ft_strncmp(shell->arg, "--", 3) == 0)
		return (ft_home_dir(glo, env, shell));
	return (ft_change_dir(shell->arg, env, glo, shell));
}

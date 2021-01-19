/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:55 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/14 16:13:23 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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
	if (arg[0] == NULL)
		return (ft_home_dir(glo, env, arg));
	if (((ft_strncmp(arg[0], " ", 1) != 0) && input[2] != ' ' && \
		input[2] != '\t' && input[2] != '\v'))
		return (free_tab_ret(arg));
	arg[0] = ft_cd_args_check(arg, env, glo);
	if (glo->i == FALSE)
		return (free_tab_ret(arg));
	if (arg[0][0] == '-' && (arg[0][1] == ' ' || arg[0][1] == '\t' \
		|| arg[0][1] == '\v' || arg[0][1] == '\f' || arg[0][1] == 0))
		return (ft_oldpwd(glo, arg));
	free(glo->oldpwd);
	if (!(glo->oldpwd = getcwd(NULL, 0)))
		return (free_tab_ret(arg));
	if (ft_strncmp(arg[0], "--", 3) == 0 || ft_strncmp(arg[0], " ", 1) == 0)
		return (ft_home_dir(glo, env, arg));
	return (ft_change_dir(arg[0], env, glo, arg));
}

int		ft_oldpwd(t_struct *glo, char **arg)
{
	char		*buf;

	if ((buf = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd(strerror(errno), 1);
		free(buf);
		return (TRUE);
	}
	if (glo->cd_count == 0)
	{
		ft_putstr_fd("OLDPWD not set\n", 1);
		free(buf);
		return (free_tab_ret(arg));
	}
	ft_cd_error(glo->oldpwd);
	ft_putstr_fd(glo->oldpwd, 1);
	write(1, "\n", 1);
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(buf)))
		exit(EXIT_FAILURE);
	glo->cd_count++;
	free(buf);
	free_tab_ret(arg);
	return (TRUE);
}

int		ft_cd_error(char *arg)
{
	if (chdir(arg) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	return (TRUE);
}

char	*ft_cd_args_check(char **arg, char **env, t_struct *glo)
{
	if (arg[1] != NULL)
	{
		ft_putstr_fd("too many arguments", 1);
		write(1, "\n", 1);
		glo->i = FALSE;
		return (arg[0]);
	}
	if (arg[0][0] == '~')
	{
		if (!(ft_tilde(arg, env, glo)))
			exit(EXIT_FAILURE);
	}
	glo->i = TRUE;
	return (ft_cd_env(arg, env, glo));
}

char	*ft_cd_env(char **arg, char **env, t_struct *glo)
{
	glo->i = 0;
	while (arg[0][glo->i])
	{
		if (arg[0][glo->i] == '$')
		{
			glo->y = glo->i;
			while (arg[0][glo->y] && arg[0][glo->y] != '/')
				glo->y++;
			arg[0] = ft_cd_env_sub(arg[0], env, glo);
		}
		glo->i++;
	}
	return (arg[0]);
}

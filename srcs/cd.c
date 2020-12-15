/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:55 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/15 18:10:56 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_cd(char *input, char **env, t_struct *glo)
{
	char	**arg;
	char	buf[200];
	char	*temp;

	if (ft_strncmp("cd", input, 2) == 0)
	{
		if (!(temp = ft_substr(input, 2, ft_strlen(input))))
			return (FALSE);
		if (!(arg = ft_split(temp, ' ')))
			return (FALSE);
		free(temp);
	}
	else
		return (TRUE);
	if (arg[0] == NULL)
		return (ft_home_dir(glo, env, arg));
	if (((ft_strncmp(arg[0], " ", 1) != 0) && input[2] != ' ' && input[2] != '\t' && input[2] != '\v'))
		return (free_tab_ret(arg));
	if (ft_cd_args_check(arg, env, glo) == FALSE)
		return (FALSE);
	if (ft_cd_args_check(arg, env, glo) == TRUE)
		return (free_tab_ret(arg));
	if (ft_cd_env(arg, env, glo) == FALSE)
		return (FALSE);
	if (arg[0][0] == '-' && (arg[0][1] == ' ' || arg[0][1] == '\t' || arg[0][1] == '\v' || arg[0][1] == '\f' || arg[0][1] == 0))
		return (ft_oldpwd(glo, arg));
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(getcwd(buf, 200))))
		return (free_tab_ret(arg));
	if (ft_strncmp(arg[0], "--", 3) == 0 || ft_strncmp(arg[0], " ", 1) == 0)
		return (ft_home_dir(glo, env, arg));
	return (ft_change_dir(arg[0], env, glo, arg));
}

int		ft_oldpwd(t_struct *glo, char **arg)
{
	char		buf[200];
	char		*temp;

	if (!(temp = ft_strdup(getcwd(buf, 200))))
		return (FALSE);
	if (glo->cd_count == 0)
	{
		ft_putstr_fd("OLDPWD not set\n", 1);
		free(temp);
		return (free_tab_ret(arg));
	}
	ft_cd_error(glo->oldpwd);
	ft_putstr_fd(glo->oldpwd, 1);
	write(1, "\n", 1);
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(temp)))
	{
		free(temp);
		free(arg);
		return (FALSE);
	}
	free(temp);
	glo->cd_count++;
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

int		ft_cd_args_check(char **arg, char **env, t_struct *glo)
{
	if (arg[1] != NULL)
	{
		ft_putstr_fd("too many arguments", 1);
		write(1, "\n", 1);
		return (TRUE);
	}
	if (arg[0][0] == '~')
	{
		if (!(ft_tilde(arg, env, glo)))
			return (FALSE);
	}
	return (2);
}

int		ft_cd_env(char **arg, char **env, t_struct *glo)
{
	int		i;
	char	*temp;
	int		y;
	char	*temp2;

	i = 0;
	while (arg[0][i])
	{
		if (arg[0][i] == '$')
		{
			y = i;
			while (arg[0][y] && arg[0][y] != '/')
				y++;
			temp = ft_substr(arg[0], i, y);
			save_env(temp, env, glo);
			free(temp);
			temp = ft_substr(arg[0], 0, i);
			temp2 = ft_strjoin(temp, glo->env);
			free(temp);
			temp = ft_substr(arg[0], y, ft_strlen(arg[0]) - y);
			free(arg[0]);
			arg[0] = ft_strjoin(temp2, temp);
			free(temp2);
			free(temp);
		}
		i++;
	}
	return (TRUE);
}

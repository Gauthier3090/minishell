/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:55 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/09 16:50:19 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_cd(char *input, char **env, t_struct *glo)
{
	char	**arg;
	char	buf[200];

	if ((ft_strncmp("cd", input, 2) == 0) && (input[2] == ' ' || input[2] == '\t' || input[2] == '\v' || input[2] == '\f' || input[2] == 0))
		arg = ft_split(ft_substr(input, 2, ft_strlen(input)), ' ');
	if ((ft_strncmp("cd", arg, 2) == 0) && (ft_strlen(input) == 2))
		arg[0] = ft_strdup(" ");
	else
		return (TRUE);
	ft_putstr_fd(input, 1);
	ft_putstr_fd(ft_itoa(ft_strlen(arg[0])), 1);
	if (ft_cd_args_check(arg) == 1)
		return (TRUE);
	if (arg[0][0] == '-' && (arg[0][1] == ' ' || arg[0][1] == '\t' || arg[0][1] == '\v' || arg[0][1] == '\f' || arg[0][1] == 0))
		return(ft_oldpwd(glo));
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(getcwd(buf, 200))))
		return (FALSE);
	if (ft_strncmp(arg[0], "--", 3) == 0 || ft_strncmp(arg[0], " ", 1) == 0)
		return (ft_home_dir(glo, env));
return (ft_change_dir(arg[0], env, glo));
}

int		ft_oldpwd(t_struct *glo)
{
	char		buf[200];
	char		*temp;

	if (!(temp = ft_strdup(getcwd(buf, 200))))
		return (FALSE);
	if (glo->cd_count == 0)
		{
			ft_putstr_fd("OLDPWD not set\n", 1);
			return (TRUE);
		}
	ft_cd_error(glo->oldpwd);
	ft_putstr_fd(glo->oldpwd, 1);
	write(1, "\n", 1);
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(temp)))
	{
		free(temp);
		return (FALSE);
	}
	free(temp);
	glo->cd_count++;
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

int		ft_cd_args_check(char **arg)
{
	if (arg[1] != NULL)
		{
			ft_putstr_fd("too many arguments", 1);
			write(1, "\n", 1);
			return (1);
		}
return (0);
}

int		ft_change_dir(char *arg, char **env, t_struct *glo)
{
save_env("$HOME", env, glo);
if (ft_strhomelen(glo) == FALSE)
		return (FALSE);
if (ft_strncmp(arg, "..", 3) == 0 && ft_strncmp(glo->oldpwd, glo->env, glo->cd_len + 1) == 0)
	{
		glo->cd_count++;
		return (TRUE);
	}
if (chdir(arg) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
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
	return (FALSE);
free(glo->env);
if (!(glo->env = ft_substr(temp, 0, glo->cd_len)))
	return (FALSE);
free(temp);
return (TRUE);
}

int		ft_home_dir(t_struct *glo, char **env)
{
save_env("$HOME", env, glo);
if (ft_strhomelen(glo) == FALSE)
		return (FALSE);
if (chdir(glo->env) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	glo->cd_count++;
return (TRUE);
}

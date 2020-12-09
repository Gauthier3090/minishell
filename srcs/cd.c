/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:55 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/09 22:56:28 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_cd(char *input, char **env, t_struct *glo)
{
	char	**arg;
	char	buf[200];

	if (ft_strncmp("cd", input, 2) == 0)
		arg = ft_split(ft_substr(input, 2, ft_strlen(input)), ' ');
	else
		return (TRUE);
	if (arg[0] == NULL)
		{
		free(arg[0]);
		arg[0] = ft_strdup(" ");
		}
	if(((ft_strncmp(arg[0], " ", 1) != 0) && input[2] != ' ' && input[2] != '\t' && input[2] != '\v'))
		return (free_tab_ret(arg));
	if (ft_cd_args_check(arg) == 1)
		return (free_tab_ret(arg));
	if (arg[0][0] == '-' && (arg[0][1] == ' ' || arg[0][1] == '\t' || arg[0][1] == '\v' || arg[0][1] == '\f' || arg[0][1] == 0))
		return(ft_oldpwd(glo, arg));
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(getcwd(buf, 200))))
		{
		free_tab_ret(arg);
		return (FALSE);
		}
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

int		ft_change_dir(char *arg, char **env, t_struct *glo, char **tab)
{
save_env("$HOME", env, glo);
if (ft_strhomelen(glo) == FALSE)
		return (FALSE);
if (ft_strncmp(arg, "..", 3) == 0 && ft_strncmp(glo->oldpwd, glo->env, glo->cd_len + 1) == 0)
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
if (ft_strhomelen(glo) == FALSE)
		return (FALSE);
if (chdir(glo->env) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	glo->cd_count++;
free_tab(arg);
return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:55 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/08 17:00:05 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_cd(char *input, t_struct *glo)
{
	char	**arg;
	int		i;
	char	buf[200];


	glo->return_status = TRUE;
	i = 0;
	if ((ft_strncmp("cd", input, 2) == 0) && (input[2] == ' ' || input[2] == '\t' || input[2] == '\v' || input[2] == '\f' || input[2] == '\n'))
		arg = ft_split(ft_substr(input, 3, ft_strlen(input) - 3), ' ');
	else
		return (glo->return_status);
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		write(1, "\n", 1);
		i++;
	}
	if (ft_cd_args_check(arg) == 1)
		return (TRUE);
	if (arg[0][0] == '-' && (arg[0][1] == ' ' || arg[0][1] == '\t' || arg[0][1] == '\v' || arg[0][1] == '\f' || arg[0][1] == 0))
		return(ft_oldpwd(glo));
	free(glo->oldpwd);
	if (!(glo->oldpwd = ft_strdup(getcwd(buf, 200))))
		return (FALSE);
	if (arg[0][0] == '/')
		return (ft_absolute_path(arg[0], glo));
	else
		return (ft_relative_path(arg[0], glo));
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


int		ft_absolute_path(char *arg, t_struct *glo)
{
	if (chdir(arg) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	glo->cd_count++;
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

int		ft_relative_path(char *arg, t_struct *glo)
{
if (chdir(arg) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	glo->cd_count++;
return (TRUE);
}

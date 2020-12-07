/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:55 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/07 18:22:38 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		ft_cd(char *input)
{
	char **arg;
	int		i;

	i = 0;
	if ((ft_strncmp("cd", input, 2) == 0) && (input[2] == ' ' || input[2] == '\t' || input[2] == '\v' || input[2] == '\f' || input[2] == '\n'))
		arg = ft_split(ft_substr(input, 3, ft_strlen(input) - 3), ' ');
	else
		return ;
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		write(1, "\n", 1);
		i++;
	}
	if (ft_cd_args_check(arg) == 1)
		return ;
	if (arg[0][0] == '/')
	{
		if (ft_absolute_path(arg[0]) == 1)
			return ;
	}
	else (chdir(arg[0]));


	/*if(chdir(path) == -1)
ft_putstr_fd(1, errno);*/
}

int		ft_absolute_path(char *arg)
{
	if (chdir(arg) == -1)
	{
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
		return 1;
	}
	return (0);
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

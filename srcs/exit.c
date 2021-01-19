/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:51:37 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/19 14:14:36 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	exit_shell(char **tab, int ret)
{
	ret = 0;
	if (ft_strlen_tab(tab) > 2)
	{
		ret = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	else if (tab[1] && !ft_strisdigit(tab[1]))
		ret = 255;
	else if (tab[1])
	{
		ret = ft_atoi(tab[1]);
		if (ret < 0 || ret > 255)
			ret = 255;
	}
	exit(ret);
}

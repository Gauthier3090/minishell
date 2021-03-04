/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:10:02 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/04 14:57:47 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_pwd(t_minishell *shell)
{
	char			*buf;

	shell->ret = 0;
	if (ft_strlen_tab(shell->tab) > 2)
	{
		shell->ret = ft_putstr_error("pwd: too many arguments\n", NULL, 1);
		return ;
	}
	if ((buf = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd(strerror(errno), 1);
		shell->ret = 2;
	}
	else
		ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
}

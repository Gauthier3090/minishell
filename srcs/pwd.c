/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:10:02 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/19 14:44:17 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_pwd(t_minishell *shell)
{
	char			*buf;

	if (shell->i > 1)
		return ;
	if ((buf = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd(strerror(errno), 1);
	else
		ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
}

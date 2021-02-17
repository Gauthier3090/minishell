/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:45:59 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/17 16:46:07 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		ft_exec_ret(int ret, t_minishell *shell)
{
	if (ret != 0)
		shell->ret = 1;
	if (ret == 32512)
		shell->ret = 127;
	if (ret == 130)
		shell->ret = 130;
	if (ret == 0)
		shell->ret = 0;
}

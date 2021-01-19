/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:48:33 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/19 14:14:49 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_env(char **tab, char **env, t_minishell *shell)
{
	int	i;

	shell->ret = 0;
	if (ft_strlen_tab(tab) > 1)
	{
		shell->ret = ft_putstr_error("env: ", "operation not permitted", 1);
		return ;
	}
	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], 1);
}

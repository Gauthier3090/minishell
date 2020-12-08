/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:48:33 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/08 15:55:45 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_env(char **tab, char **env)
{
	int	i;

	if (ft_strlen_tab(tab) > 1)
		return ;
	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], 1);
}

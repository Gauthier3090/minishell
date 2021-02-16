/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:23:45 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/16 16:24:12 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_putstr_error(char *message, char *variable, int error)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(variable, 2);
	return (error);
}

void	ft_put_errno(int error_numb, t_minishell *shell)
{
	ft_putstr_fd(strerror(error_numb), 2);
	write(1, "\n", 2);
	shell->ret = 2;
}

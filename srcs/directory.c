/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:15:41 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/04 15:24:30 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	getdirectory(void)
{
	char buffer[PATH_MAX];

	getcwd(buffer, sizeof(buffer));
	ft_putstr_fd(buffer, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:09:02 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/22 23:09:31 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	export_error(char *variable, char **arg)
{
	int	i;

	i = -1;
	while (variable[++i])
	{
		if (variable[i] == '+' || variable[i] == '-')
			ft_putstr_error("export: not an identifier: ", variable);
	}
	if (ft_strisdigit(variable) && variable[0] != '\0')
		ft_putstr_error("export: not an identifier: ", variable);
	i = -1;
	while (arg[++i])
	{
		if (arg[0] != arg[i] && ft_strcmp(arg[i], "USER"))
			ft_putstr_error("export: not valid in this context: ", variable);
	}
}

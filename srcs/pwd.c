/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:10:02 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/16 23:21:12 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_pwd(char *input)
{
	int		i;
	char	*buf;

	i = 3;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
			return ;
		i++;
	}
	if ((buf = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd(strerror(errno), 1);
	else
		ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
}

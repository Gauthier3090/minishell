/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 00:11:01 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/22 15:39:40 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*delete_char_right(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (&str[i + 1]);
	}
	return (str);
}

char	*delete_char_left(char *str, char c)
{
	int		i;
	int		count;
	char	*new_str;

	i = -1;
	count = 1;
	if (!(new_str = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	while (str[++i] && str[i] != c)
	{
		if (!(new_str = ft_realloc(new_str, count + 1)))
			exit(EXIT_FAILURE);
		new_str[i] = str[i];
		count++;
	}
	return (new_str);
}

void	ft_putstr_error(char *message, char *variable)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(variable, 2);
	exit(EXIT_FAILURE);
}

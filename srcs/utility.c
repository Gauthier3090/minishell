/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:21:04 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/08 16:18:24 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_whitespace(char *input)
{
	char	*temp;
	int		i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t' || input[i] == '\v'
	|| input[i] == '\f' || input[i] == '\n'))
		i++;
	if (!(temp = ft_substr(input, i, ft_strlen(input) - i)))
		exit(EXIT_FAILURE);
	free(input);
	return (temp);
}

int		ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

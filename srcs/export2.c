/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:45:47 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/06 17:05:29 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

size_t	ft_tablen(char **tab)
{
	int		i;
	size_t	length;

	i = -1;
	length = 0;
	while (tab[++i])
	{
		length += ft_strlen(tab[i]);
		length++;
	}
	return (length);
}

char	*tabtostr(char **tab, int return_line)
{
	char	*str;
	int		i;
	int		j;
	int		index;

	if (!(str = ft_calloc(1, ft_tablen(tab) * sizeof(char))))
		return (NULL);
	i = -1;
	index = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			str[++index] = tab[i][j];
		if (i != ft_strlen_tab(tab) - 1 && return_line)
			str[++index] = '\n';
	}
	return (str);
}

void	sorting_env(char **env, int size)
{
	int		i;
	int		j;
	char	*tmp;
	char	**tab;

	tmp = tabtostr(env, TRUE);
	if (!(tab = ft_split(tmp, '\n')))
		exit(EXIT_FAILURE);
	free(tmp);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (ft_strcmp(tab[i], tab[j]) < 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
	ft_print_tab(tab);
	free_tab(tab);
}

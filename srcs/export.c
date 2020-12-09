/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/09 16:14:50 by gpladet          ###   ########.fr       */
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

char	*tabtostr(char **tab)
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
		if (i != ft_strlen_tab(tab) - 1)
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

	i = -1;
	tmp = tabtostr(env);
	if (!(tab = ft_split(tmp, '\n')))
		exit(EXIT_FAILURE);
	free(tmp);
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

void	export(char **tab, char **env)
{
	if (ft_strlen_tab(tab) == 1)
		sorting_env(env, ft_strlen_tab(env));
}

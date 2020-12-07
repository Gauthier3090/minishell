/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:34:12 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/07 16:50:22 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	directoryprompt(void)
{
	char	*pwd;
	char	buffer[PATH_MAX];
	char	**tab;
	int		i;
	int		last;

	pwd = getcwd(buffer, sizeof(buffer));
	if (!(tab = ft_split(pwd, '/')))
		exit(EXIT_FAILURE);
	i = -1;
	last = 0;
	while (tab[++i])
		last++;
	ft_putstr_fd(GREEN "➜" RESET "  " CYAN, 1);
	ft_putstr_fd(tab[last - 1], 1);
	ft_putstr_fd(RESET " ", 1);
	free_tab(tab);
}

char	*getinput(void)
{
	int		ret;
	int		i;
	int		count;
	char	buffer;
	char	*input;

	if (!(input = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	count = 1;
	while ((ret = read(0, &buffer, 1)) && buffer != '\n')
	{
		input[++i] = buffer;
		count++;
		input = ft_realloc(input, count + 1);
	}
	return (input);
}

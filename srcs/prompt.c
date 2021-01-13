/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:34:12 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/12 15:53:48 by ldavids          ###   ########.fr       */
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

	if (!(input = ft_calloc(2, sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	count = 1;
	while ((ret = read(0, &buffer, 1)) && buffer != '\n')
	{
		input[++i] = buffer;
		count++;
		if (!(input = ft_realloc(input, count + 1)))
			exit(EXIT_FAILURE);
	}
	return (input);
}

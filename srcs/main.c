/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/07 17:46:20 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int argc, char **argv, char **env)
{
	int		is_active;
	char	*input;
	char	**tab;

	is_active = 1;
	(void)argc;
	(void)argv;
	while (is_active)
	{
		directoryprompt();
		input = getinput();
		if (!(tab = ft_split(input, ' ')))
			exit(EXIT_FAILURE);
		if (ft_strncmp(tab[0], "echo", ft_strlen(input)) == 0)
			echo(tab, env);
		if (ft_strncmp(tab[0], "exit", ft_strlen(input)) == 0)
			exit(EXIT_SUCCESS);
		free(input);
	}
}

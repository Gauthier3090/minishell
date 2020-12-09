/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/09 14:07:13 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int argc, char **argv, char **env)
{
	int			is_active;
	char		*input;
	char		**tab;
	t_struct	*glo;

	is_active = 1;
	(void)argc;
	(void)argv;
	if (!(glo = malloc(sizeof(t_struct))))
		exit(EXIT_FAILURE);
	if (ft_struct_init(glo) == FALSE)
		exit(EXIT_FAILURE);
	while (is_active)
	{
		directoryprompt();
		input = getinput();
		input = ft_whitespace(input);
		if (!(tab = ft_split(input, ' ')))
			exit(EXIT_FAILURE);
		if (ft_strncmp(tab[0], "echo", ft_strlen(input)) == 0)
			echo(tab, env);
		if (ft_strncmp(tab[0], "exit", ft_strlen(input)) == 0)
			exit_shell(tab);
		if (ft_strncmp(tab[0], "env", ft_strlen(input)) == 0)
			ft_env(tab, env);
		if (ft_cd(input, env, glo) == FALSE)
			exit(EXIT_FAILURE);
		free(input);
	}
}

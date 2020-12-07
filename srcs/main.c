/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:48:26 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/07 15:23:40 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(void)
{
	int		is_active;
	char	*input;

	is_active = 1;
	while (is_active)
	{
		directoryprompt();
		input = getinput();
		path();
		free(input);
	}
}

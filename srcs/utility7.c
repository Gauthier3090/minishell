/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:38:46 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/01 15:36:45 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char		*ft_backs_whitespace(t_minishell *shell, char *str)
{
	char	*temp;
	int		i;

	i = 0;
	while (shell->white > 0)
	{
		shell->white--;
		i++;
	}
	if (!(temp = ft_substr(str, i, ft_strlen(str) - i)))
		exit(EXIT_FAILURE);
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}


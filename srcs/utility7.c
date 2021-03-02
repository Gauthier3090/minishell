/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:38:46 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/02 14:44:48 by ldavids          ###   ########.fr       */
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
	if (!(temp = ft_substr(str, i, ft_strlen(str))))
		exit(EXIT_FAILURE);
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

char		*ft_backzero(char *str)
{
	int		x;

	x = 0;
	while (str[x])
	{
		str[x] = '0';
		x++;
	}
	x = 0;
	return (str);
}

int			ft_voided_char_input(int i, t_minishell *shell)
{
	if (shell->backs_input[i] && shell->backs_input[i] != '0')
		return (TRUE);
	return (FALSE);
}

int			ft_voided_char(int i, int x, t_minishell *shell)
{
	if (shell->backs_tab[x][i] && shell->backs_tab[x][i] != '0')
		return (TRUE);
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:08:57 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/23 15:11:44 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		research_char(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (TRUE);
	}
	return (FALSE);
}

void	exception_export_more(t_minishell *shell)
{
	char	*tmp;
	char	*str;

	str = delete_char_right(shell->variable, '=');
	if (!(str = ft_strjoin(str, "=")))
		exit(EXIT_FAILURE);
	if (!(tmp = ft_strjoin(str, shell->value)))
		exit(EXIT_FAILURE);
	free(shell->value);
	if (!(shell->value = ft_strdup(tmp)))
		exit(EXIT_FAILURE);
	free(tmp);
	free(str);
	str = delete_char_left(shell->variable, '=');
	free(shell->variable);
	if (!(shell->variable = ft_strdup(str)))
		exit(EXIT_FAILURE);
	free(str);
}

void	exception_export(t_minishell *shell)
{
	char	*str;

	if (shell->variable && !shell->value && research_char(shell->variable, '='))
	{
		str = delete_char_right(shell->variable, '=');
		if (!(shell->value = ft_strdup(str)))
			exit(EXIT_FAILURE);
		str = delete_char_left(shell->variable, '=');
		free(shell->variable);
		if (!(shell->variable = ft_strdup(str)))
			exit(EXIT_FAILURE);
		free(str);
	}
	else if (shell->variable && shell->value &&
	research_char(shell->variable, '='))
		exception_export_more(shell);
}

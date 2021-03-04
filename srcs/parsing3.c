/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:24:17 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/04 14:52:42 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*found_env_exeception(char *str, int ret)
{
	if (str[0] == '?')
	{
		free(str);
		return (ft_itoa(ret));
	}
	if (str[0] == '$')
	{
		free(str);
		if (!(str = ft_strdup("$")))
			exit(EXIT_FAILURE);
		return (str);
	}
	return (NULL);
}

int		str_env_length(char *input, int *i)
{
	int	j;
	int	len;

	j = *i;
	len = 0;
	if (input[j] == '$' && !input[j + 1])
		len = 1;
	while (input[++j])
	{
		if (!ft_isalnum(input[j]) && input[j] != '?')
			break ;
		else
			len++;
	}
	return (len);
}

char	*str_not_env_backslash(char *input, int *i)
{
	char	*str;
	int		len;
	int		j;

	j = *i;
	len = 0;
	while (input[j] && input[j] != '"')
	{
		j++;
		len++;
	}
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
	while (input[*i] && input[*i] != '"')
	{
		str[++j] = input[*i];
		(*i)++;
	}
	return (str);
}

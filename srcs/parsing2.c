/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:37:10 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/12 14:59:10 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*found_env(char *str, char **env)
{
	char	*tmp;
	int		i;

	i = -1;
	while (env[++i])
	{
		tmp = delete_char_left(env[i], '=');
		if (!ft_strcmp(str, tmp))
		{
			free(str);
			str = delete_char_right(env[i], '=');
		}
		free(tmp);
	}
	return (str);
}

char	*parse_null_quote(char *input, int *i, char **env)
{
	char	*tmp;
	char	*str;

	str = NULL;
	while (input[*i])
	{
		if (input[*i] != '$')
			tmp = str_not_env(input, i);
		else
		{
			tmp = str_env(input, i, env);
			tmp = ft_strdup(tmp);
		}
		if (!str)
		{
			if (!(str = ft_calloc(ft_strlen(tmp), sizeof(char))))
				exit(EXIT_FAILURE);
			str = ft_strcat(str, tmp);
		}
		else
			str = realloc_str(str, tmp);
		free(tmp);
	}
	return (str);
}

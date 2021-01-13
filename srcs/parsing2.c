/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:37:10 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/13 15:07:47 by gpladet          ###   ########.fr       */
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
			free(tmp);
			str = delete_char_right(env[i], '=');
			return (str);
		}
		free(tmp);
	}
	free(str);
	return (NULL);
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
			tmp ? tmp = ft_strdup(tmp) : 0;
		}
		if (!str && tmp)
		{
			if (!(str = ft_calloc(ft_strlen(tmp) + 1, sizeof(char))))
				exit(EXIT_FAILURE);
			str = ft_strcat(str, tmp);
		}
		else
			tmp ? str = realloc_str(str, tmp) : 0;
		free(tmp);
	}
	return (str);
}

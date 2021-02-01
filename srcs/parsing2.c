/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:37:10 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/01 16:04:09 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*found_env(char *str, char **env, int ret)
{
	char	*tmp;
	int		i;

	i = -1;
	if (str[0] == '?')
	{
		free(str);
		return (ft_itoa(ret));
	}
	while (env[++i])
	{
		tmp = delete_char_left(env[i], '=');
		if (!ft_strcmp(str, tmp))
		{
			free(str);
			free(tmp);
			if (!(str = ft_strdup(delete_char_right(env[i], '='))))
				exit(EXIT_FAILURE);
			return (str);
		}
		free(tmp);
	}
	free(str);
	return (NULL);
}

char	*parse_null_quote(char *input, int *i, char **env, int ret)
{
	char	*tmp;
	char	*str;

	str = NULL;
	while (input[*i] && input[*i] != '"' && input[*i] != '\'')
	{
		if (input[*i] != '$')
			tmp = str_not_env(input, i);
		else
			tmp = str_env(input, i, env, ret);
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

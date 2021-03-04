/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:37:10 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/04 14:56:54 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*found_env(char *str, char **env, int ret)
{
	char	*tmp;
	int		i;

	tmp = found_env_exeception(str, ret);
	if (tmp)
		return (tmp);
	i = -1;
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

char	*str_not_env_double_quotes(char *input, int *i)
{
	char	*str;
	int		len;
	int		j;

	j = *i;
	len = 0;
	while (input[j] && input[j] != '$' && input[j] != '"')
	{
		j++;
		len++;
	}
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
	while (input[*i] && input[*i] != '$' && input[*i] != '"')
	{
		str[++j] = input[*i];
		(*i)++;
	}
	return (str);
}

char	*str_not_env_simple_quotes(char *input, int *i)
{
	char	*str;
	int		len;
	int		j;

	j = *i;
	len = 0;
	while (input[j] && input[j] != '\'')
	{
		j++;
		len++;
	}
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
	while (input[*i] && input[*i] != '\'')
		str[++j] = input[(*i)++];
	return (str);
}

char	*str_not_env(char *input, int *i)
{
	char	*str;
	int		len;
	int		j;

	j = *i;
	len = 0;
	if (input[j] == '$')
		return (str_not_env_simple_quotes(input, i));
	while (input[j] && input[j] != '$' && input[j] != '"' && input[j] != '\'')
	{
		j++;
		len++;
	}
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
	while (input[*i] && input[*i] != '$' && input[*i] != '"'
	&& input[*i] != '\'')
		str[++j] = input[(*i)++];
	return (str);
}

char	*str_env(char *input, int *i, char **env, int ret)
{
	int		len;
	int		j;
	char	*str;

	if (input[*i] == '$' && input[*i + 1] == '$')
		return (str_not_env_backslash(input, i));
	len = str_env_length(input, i);
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
	if (input[*i] == '$' && !input[*i + 1])
		str[++j] = input[*i];
	while (input[++(*i)])
	{
		if (!ft_isalnum(input[*i]) && input[*i] != '?')
			break ;
		else
			str[++j] = input[*i];
	}
	str = found_env(str, env, ret);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:40:50 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/02 22:19:36 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*parse_simple_quote(char *input, int *i)
{
	char	*str;
	int		j;
	int		len;

	(*i)++;
	j = *i;
	len = 0;
	while (input[j] != '\'')
	{
		len++;
		j++;
	}
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
	while (input[*i] != '\'')
		str[++j] = input[(*i)++];
	return (str);
}

char	*parse_double_quote(char *input, int *i, char **env, int ret)
{
	char	*tmp;
	char	*str;

	(*i)++;
	str = NULL;
	while (input[*i] != '"')
	{
		if (input[*i] != '$')
			tmp = str_not_env_double_quotes(input, i);
		else
			tmp = str_env(input, i, env, ret);
		tmp ? str = realloc_str(str, tmp) : 0;
		free(tmp);
	}
	return (str);
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
		tmp ? str = realloc_str(str, tmp) : 0;
		free(tmp);
	}
	return (str);
}

char	*parse_input(char *input, char **env, int ret)
{
	int		i;
	char	*str;
	char	*final_str;

	final_str = NULL;
	if (input)
	{
		i = 0;
		while ((size_t)i < ft_strlen(input) - 1)
		{
			if (input[i] == '\'')
				str = parse_simple_quote(input, &i);
			else if (input[i] == '"')
				str = parse_double_quote(input, &i, env, ret);
			else
				str = parse_null_quote(input, &i, env, ret);
			str ? final_str = realloc_str(final_str, str) : 0;
			free(str);
		}
		if (!final_str)
		{
			if (!(final_str = ft_strdup("")))
				exit(EXIT_FAILURE);
		}
		return (final_str);
	}
	return (NULL);
}

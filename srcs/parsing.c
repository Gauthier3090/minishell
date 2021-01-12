/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:40:50 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/12 14:59:05 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*parse_simple_quote(char *input, int *i)
{
	char	*str;
	int		count;
	int		len;

	(*i)++;
	if (!(str = ft_calloc(2, sizeof(char))))
		exit(EXIT_FAILURE);
	count = 1;
	len = -1;
	while (input[*i] != '\'')
	{
		if (input[*i] == '\\' && (input[*i + 1] == '\\'))
			(*i)++;
		str[++len] = input[*i];
		count++;
		if (!(str = ft_realloc(str, count)))
			exit(EXIT_FAILURE);
		(*i)++;
	}
	return (str);
}

char	*str_env(char *input, int *i, char **env)
{
	int		len;
	int		count;
	char	*str;

	if (!(str = ft_calloc(2, sizeof(char))))
		exit(EXIT_FAILURE);
	len = -1;
	count = 1;
	while (input[(++(*i))])
	{
		if (!ft_isalnum(input[*i]))
			break ;
		else
		{
			str[++len] = input[*i];
			count++;
			if (!(str = ft_realloc(str, count)))
				exit(EXIT_FAILURE);
		}
	}
	str = found_env(str, env);
	return (str);
}

char	*str_not_env(char *input, int *i)
{
	char	*str;
	int		count;
	int		len;

	if (!(str = ft_calloc(2, sizeof(char))))
		exit(EXIT_FAILURE);
	count = 1;
	len = -1;
	while (input[*i] != '$' && input[*i] != '"' && input[*i])
	{
		if (input[*i] == '\\' && (input[*i + 1] == '\\'))
			(*i)++;
		str[++len] = input[*i];
		count++;
		if (!(str = ft_realloc(str, count)))
			exit(EXIT_FAILURE);
		(*i)++;
	}
	return (str);
}

char	*parse_double_quote(char *input, int *i, char **env)
{
	char	*tmp;
	char	*str;

	(*i)++;
	str = NULL;
	while (input[*i] != '"')
	{
		if (input[*i] != '$')
			tmp = str_not_env(input, i);
		else
		{
			tmp = str_env(input, i, env);
			if (!(tmp = ft_strdup(tmp)))
				exit(EXIT_FAILURE);
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

char	*parse_input(char *input, char **env)
{
	int		i;
	char	*str;
	char	*parsing_str;

	if (input)
	{
		if (!(parsing_str = ft_calloc(2, sizeof(char))))
			exit(EXIT_FAILURE);
		i = -1;
		while (input[++i])
		{
			if (input[i] == '\'')
				str = parse_simple_quote(input, &i);
			else if (input[i] == '"')
				str = parse_double_quote(input, &i, env);
			else
				str = parse_null_quote(input, &i, env);
			parsing_str = realloc_str(parsing_str, str);
			free(str);
		}
		return (parsing_str);
	}
	return (NULL);
}

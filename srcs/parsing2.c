/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:37:10 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/23 16:51:59 by ldavids          ###   ########.fr       */
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
		/*if (input[*i] == '\\' && input[*i + 1] == '\\')
			(*i)++;*/
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
		/*if (input[j] == '$' && simple_quote)
			break ;*/
		j++;
		len++;
	}
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
	while (input[*i] && input[*i] != '\'')
	{
		/*if (input[*i] == '\\' && input[*i + 1] == '\\')
			(*i)++;*/
		str[++j] = input[(*i)++];
		/*if (input[*i] == '$' && simple_quote)
			break ;*/
	}
	return (str);
}

char	*str_not_env(char *input, int *i)
{
	char	*str;
	int		len;
	int		j;

	j = *i;
	len = 0;
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

	j = *i;
	len = 0;
	while (input[++j])
	{
		if (!ft_isalnum(input[j]) && input[j] != '?')
			break ;
		else
			len++;
	}
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
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

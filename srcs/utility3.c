/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 00:11:01 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/16 16:22:49 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*delete_char_right(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == c)
			return (&str[i + 1]);
	}
	return (NULL);
}

int		ft_strlen_split_quotes(char *str, int *i, int *len)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		*len += 2;
		while (str[*i] != '\'')
		{
			(*len)++;
			(*i)++;
		}
		return (TRUE);
	}
	else if (str[*i] == '"')
	{
		(*i)++;
		*len += 2;
		while (str[*i] != '"')
		{
			(*len)++;
			(*i)++;
		}
		return (TRUE);
	}
	return (FALSE);
}

int		ft_strlen_split(char *str, char c)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_strlen_split_quotes(str, &i, &len))
			continue ;
		else if (str[i] == c)
			break ;
		else
			len++;
	}
	return (len);
}

int		delete_char_left_quotes(char *str, char **new_str, int *i, int *j)
{
	if (str[*i] == '\'')
	{
		(*new_str)[++(*j)] = str[(*i)++];
		while (str[*i] != '\'')
			(*new_str)[++(*j)] = str[(*i)++];
		(*new_str)[++(*j)] = str[*i];
		return (TRUE);
	}
	else if (str[*i] == '"')
	{
		(*new_str)[++(*j)] = str[(*i)++];
		while (str[*i] != '"')
			(*new_str)[++(*j)] = str[(*i)++];
		(*new_str)[++(*j)] = str[*i];
		return (TRUE);
	}
	return (FALSE);
}

char	*delete_char_left(char *str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = ft_strlen_split(str, c);
	if (!(new_str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (delete_char_left_quotes(str, &new_str, &i, &j))
			continue ;
		else if (str[i] == c)
			break ;
		else
			new_str[++j] = str[i];
	}
	return (new_str);
}

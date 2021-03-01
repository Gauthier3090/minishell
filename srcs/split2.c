/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:42:27 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/25 17:08:15 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		count_quotes(char *str, int *i)
{
	int quotes;
	int	quotes2;
	int	count;

	quotes = 0;
	quotes2 = 0;
	count = 0;
	count++;
	while (str[*i])
	{
		if (str[*i] == '\'')
			quotes++;
		else if (str[*i] == '"')
			quotes2++;
		if (str[*i] == ' ')
		{
			if (quotes % 2 == 0 && quotes2 % 2 == 0)
			{
				(*i)++;
				break ;
			}
		}
		(*i)++;
	}
	return (count);
}

void	count_words_space(char *str, int *i)
{
	while (str[*i] != ' ' && str[*i])
	{
		(*i)++;
		if (str[*i] == '"')
		{
			(*i)++;
			while (str[*i] != '"')
				(*i)++;
		}
		if (str[*i] == '\'')
		{
			(*i)++;
			while (str[*i] != '\'')
				(*i)++;
		}
	}
}

int		count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (str[i] == '\'')
			count += count_quotes(str, &i);
		else if (str[i] == '"')
			count += count_quotes(str, &i);
		else
		{
			if (str[i] != ' ')
				count++;
			i++;
			count_words_space(str, &i);
		}
	}
	return (count);
}

void	size_words_null_quotes(char *str, int *i, int *size)
{
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '"')
		{
			(*i)++;
			while (str[*i] != '"' && str[*i])
			{
				(*size)++;
				(*i)++;
			}
			*size += 2;
		}
		else if (str[*i] == '\'')
		{
			(*i)++;
			while (str[*i] != '\'' && str[*i])
			{
				(*size)++;
				(*i)++;
			}
			*size += 2;
		}
		(*size)++;
		(*i)++;
	}
}

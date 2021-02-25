/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:27:21 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/23 18:48:29 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		size_quotes(char *str, int *i, int quotes, int quotes2)
{
	int	size;

	size = 0;
	while (str[*i])
	{
		if (str[*i] == '\'')
			quotes++;
		else if (str[*i] == '"')
			quotes2++;
		if (quotes % 2 == 0 && quotes2 % 2 == 0 && str[*i] == ' ')
		{
			size++;
			(*i)++;
			break ;
		}
		else
		{
			size++;
			(*i)++;
		}
	}
	return (size);
}

int		size_words(char *str)
{
	int	i;
	int	size;
	int	quotes;
	int	quotes2;

	i = 0;
	size = 0;
	quotes = 0;
	quotes2 = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\'')
		size += size_quotes(str, &i, quotes, quotes2);
	else if (str[i] == '"')
		size += size_quotes(str, &i, quotes, quotes2);
	else
		size_words_null_quotes(str, &i, &size);
	return (size);
}

void	split_quotes(char **tab, char *str, int i, int *j)
{
	int	k;
	int	quotes;
	int	quotes2;

	k = -1;
	quotes = 0;
	quotes2 = 0;
	while (str[*j])
	{
		if (str[*j] == '\'')
			quotes++;
		else if (str[*j] == '"')
			quotes2++;
		if (quotes % 2 == 0 && quotes2 % 2 == 0 && str[*j] == ' ')
			break ;
		else
			tab[i][++k] = str[(*j)++];
	}
}

void	split_null_quotes(char **tab, char *str, int i, int *j)
{
	int	k;

	k = -1;
	while (str[*j] != ' ' && str[*j])
	{
		if (str[*j] == '"')
		{
			tab[i][++k] = str[(*j)++];
			while (str[*j] != '"')
				tab[i][++k] = str[(*j)++];
			tab[i][++k] = str[(*j)++];
		}
		else if (str[*j] == '\'')
		{
			tab[i][++k] = str[(*j)++];
			while (str[*j] != '\'')
				tab[i][++k] = str[(*j)++];
			tab[i][++k] = str[(*j)++];
		}
		else
			tab[i][++k] = str[(*j)++];
	}
}

char	**split_input(char *str)
{
	int		count;
	int		i;
	int		j;
	char	**tab;

	count = count_words(str);
	if (!(tab = (char **)ft_calloc(count + 1, sizeof(char *))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (++i < count)
	{
		if (!(tab[i] = ft_calloc(size_words(&str[j]) + 1, sizeof(char))))
			exit(EXIT_FAILURE);
		while (str[j] == ' ')
			j++;
		if (str[j] == '\'')
			split_quotes(tab, str, i, &j);
		else if (str[j] == '"')
			split_quotes(tab, str, i, &j);
		else
			split_null_quotes(tab, str, i, &j);
	}
	return (tab);
}

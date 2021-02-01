/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 00:11:01 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/01 16:27:31 by gpladet          ###   ########.fr       */
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

char	*delete_char_left(char *str, char c)
{
	int		i;
	int		j;
	int		count;
	char	*new_str;

	i = -1;
	j = -1;
	count = 1;
	if (!(new_str = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			new_str[++j] = str[i];
			i++;
			count++;
			while (str[i] != '\'')
			{
				if (!(new_str = ft_realloc(new_str, count + 3)))
					exit(EXIT_FAILURE);
				new_str[++j] = str[i];
				count++;
				i++;
			}
			new_str[++j] = str[i];
		}
		else if (str[i] == '"')
		{
			new_str[++j] = str[i];
			i++;
			count++;
			while (str[i] != '"')
			{
				if (!(new_str = ft_realloc(new_str, count + 3)))
					exit(EXIT_FAILURE);
				new_str[++j] = str[i];
				count++;
				i++;
			}
			new_str[++j] = str[i];
		}
		else if (str[i] != c)
		{
			if (!(new_str = ft_realloc(new_str, count + 2)))
				exit(EXIT_FAILURE);
			new_str[++j] = str[i];
			count++;
		}
		else if (str[i] == c)
			break ;
	}
	return (new_str);
}

int		ft_putstr_error(char *message, char *variable, int error)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(variable, 2);
	return (error);
}

void	ft_put_errno(int error_numb)
{
	ft_putstr_fd(strerror(error_numb), 2);
	write(1, "\n", 2);
}

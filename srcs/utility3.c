/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 00:11:01 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/06 17:09:12 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*delete_char_right(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (&str[i + 1]);
	}
	return (NULL);
}

char	*delete_char_left(char *str, char c)
{
	int		i;
	int		count;
	char	*new_str;

	i = -1;
	count = 1;
	if (!(new_str = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	while (str[++i] && str[i] != c)
	{
		if (!(new_str = ft_realloc(new_str, count + 1)))
			exit(EXIT_FAILURE);
		new_str[i] = str[i];
		count++;
	}
	return (new_str);
}

int		variable_exist(char **env, char *str)
{
	int	i;
	int	j;
	int	length;

	i = -1;
	length = ft_strlen(str);
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], str, j) && !ft_strncmp(env[i], str, length))
			return (i);
	}
	return (-1);
}

void	ft_putstr_error(char *message, char *variable)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(variable, 2);
}

void	ft_put_errno(int error_numb)
{
	ft_putstr_fd(strerror(error_numb), 2);
		write(1, "\n", 1);
}

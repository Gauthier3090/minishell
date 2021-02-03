/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 00:11:01 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/02 22:30:33 by ldavids          ###   ########.fr       */
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

int		ft_strlen_split(char *str, char c)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			break ;
		else
			len++;
	}
	return (len);
}

char	*delete_char_left(char *str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = ft_strlen_split(str, c);
	if (!(new_str = calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == c)
			break ;
		else
			new_str[++j] = str[i];
	}
	return (new_str);
}

int		ft_putstr_error(char *message, char *variable, int error)
{
	ft_putstr_fd(message, 2);
	ft_putendl_fd(variable, 2);
	return (error);
}

void	ft_put_errno(int error_numb, t_minishell *shell)
{
	ft_putstr_fd(strerror(error_numb), 2);
	write(1, "\n", 2);
	shell->ret = 2;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:47:21 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/15 15:48:30 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		error_redirection(char *error, char *var, int ret)
{
	ft_putstr_error(error, var, ret);
	return (FALSE);
}

int		ft_count_redirection_right(char *str, int *i)
{
	int	count;

	count = 0;
	while (str[*i] == '>' && str[*i])
	{
		count++;
		(*i)++;
		while (str[*i] == ' ')
			(*i)++;
		if (str[*i] == '>' && str[*i + 1] == '>')
			return (error_redirection(ERROR_REDIRECTION_RIGHT, NULL, 1));
		else if (str[*i] == '<')
			return (error_redirection(ERROR_REDIRECTION_LEFT, NULL, 1));
	}
	if (count == 3)
		return (error_redirection(ERROR_REDIRECTION_SIMPLE, NULL, 1));
	else if (count > 3)
		return (error_redirection(ERROR_REDIRECTION_RIGHT, NULL, 1));
	return (TRUE);
}

int		ft_count_redirection_left(char *str, int *i)
{
	int	count;

	count = 0;
	while (str[*i] == '<' && str[*i])
	{
		count++;
		(*i)++;
		while (str[*i] == ' ')
			(*i)++;
		if (str[*i] == '>' && str[*i + 1] == '>')
			return (error_redirection(ERROR_REDIRECTION_RIGHT, NULL, 1));
		else if (str[*i] == '>')
			return (error_redirection(ERROR_REDIRECTION_SIMPLE, NULL, 1));
	}
	if (count > 1)
		return (error_redirection(ERROR_REDIRECTION_LEFT, NULL, 1));
	return (TRUE);
}

int		ft_main_count_redirection(char *str, int *i)
{
	if (str[0] == '>')
		return (error_redirection(ERROR_REDIRECTION_SIMPLE, NULL, 1));
	if (str[0] == '<')
		return (error_redirection(ERROR_REDIRECTION_LEFT, NULL, 1));
	if (str[*i] == '>' && *i != 0)
	{
		if (!(ft_count_redirection_right(str, i)))
			return (FALSE);
	}
	if (str[*i] == '<' && *i != 0)
	{
		if (!(ft_count_redirection_left(str, i)))
			return (FALSE);
	}
	return (TRUE);
}

int		ft_count_redirection(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!(tmp = ft_strtrim(str, " ")))
		exit(EXIT_FAILURE);
	if (tmp[ft_strlen(tmp) - 1] == '>' || tmp[ft_strlen(tmp) - 1] == '<')
	{
		free(tmp);
		return (error_redirection(ERROR_REDIRECTION_EMPTY, NULL, 1));
	}
	free(tmp);
	while (str[++i])
	{
		if (!(ft_main_count_redirection(str, &i)))
			return (FALSE);
	}
	return (TRUE);
}

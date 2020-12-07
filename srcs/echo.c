/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:46:38 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/07 18:31:46 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*delete_char(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (&str[i + 1]);
	}
	return (str);
}

void	echo_env(char *tab, char **env, int endline, int i)
{
	int		j;
	char	*tmp;

	j = -1;
	if (ft_strncmp(tab, "$", ft_strlen(tab)) == 0)
	{
		if ((i > 1 && endline == TRUE) || (i > 2 && endline == FALSE))
			ft_putchar_fd(' ', 1);
		ft_putchar_fd('$', 1);
		return ;
	}
	tmp = ft_substr(tab, 1, ft_strlen(tab));
	while (env[++j])
	{
		if (ft_strnstr(env[j], tmp, ft_strlen(tmp)))
		{
			if ((i > 1 && endline == TRUE) || (i > 2 && endline == FALSE))
				ft_putchar_fd(' ', 1);
			ft_putstr_fd(delete_char(env[j], '='), 1);
			break ;
		}
	}
	free(tmp);
}

void	echo(char **tab, char **env)
{
	int	i;
	int	endline;

	endline = TRUE;
	i = 0;
	if (!(ft_strncmp(tab[1], "-n", ft_strlen(tab[1]))))
	{
		i = 1;
		endline = FALSE;
	}
	while (tab[++i])
	{
		if (tab[i][0] == '$')
			echo_env(tab[i], env, endline, i);
		else
		{
			if ((i > 1 && endline == TRUE) || (i > 2 && endline == FALSE))
				ft_putchar_fd(' ', 1);
			ft_putstr_fd(tab[i], 1);
		}
	}
	if (endline)
		ft_putchar_fd('\n', 1);
}

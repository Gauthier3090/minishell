/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:46:38 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/21 22:12:38 by gpladet          ###   ########.fr       */
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

int		check_symbols(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '$')
			return (FALSE);
	}
	return (TRUE);
}

void	echo_env(char *tab, char **env)
{
	int		i;
	int		j;
	char	**arg;

	i = -1;
	while (tab[++i])
	{
		if (tab[i] != '$')
			ft_putchar_fd(tab[i], 1);
		else
			break ;
	}
	if (!(arg = ft_split(&tab[i], '$')))
		exit(EXIT_FAILURE);
	i = -1;
	while (arg[++i])
	{
		j = -1;
		while (env[++j])
		{
			if (ft_strnstr(env[j], arg[i], ft_strlen(arg[i])))
				ft_putstr_fd(delete_char(env[j], '='), 1);
		}
	}
	free_tab(arg);
}

void	echo(char **tab, char **env)
{
	int	i;
	int	n_flag;

	n_flag = FALSE;
	i = 1;
	if (ft_strlen_tab(tab) > 1)
	{
		while (tab[i] && ft_strncmp(tab[i], "-n", ft_strlen(tab[i])) == 0)
		{
			n_flag = TRUE;
			i++;
		}
		while (tab[i])
		{
			if (check_symbols(tab[i]) || !strchr(tab[i], '$'))
				ft_putstr_fd(tab[i], 1);
			else
				echo_env(tab[i], env);
			if (tab[i + 1] && tab[i][0] != '\0')
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (n_flag == FALSE)
		ft_putchar_fd('\n', 1);
}

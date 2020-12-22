/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:46:38 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/22 00:15:06 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

void	echo_env_more(char **arg, char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (arg[++i])
	{
		j = -1;
		while (env[++j])
		{
			tmp = delete_char_left(env[j], '=');
			if (ft_strcmp(tmp, arg[i]) == 0)
				ft_putstr_fd(delete_char_right(env[j], '='), 1);
			free(tmp);
		}
	}
}

void	echo_env(char *tab, char **env)
{
	int		i;
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
	echo_env_more(arg, env);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:21:04 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/04 18:00:40 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_whitespace(char *input, t_minishell *shell)
{
	char	*temp;
	int		i;

	i = 0;
	shell->white = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t' || input[i] == '\v'
	|| input[i] == '\f' || input[i] == '\n'))
	{
		shell->white++;
		i++;
	}
	if (!(temp = ft_substr(input, i, ft_strlen(input) - i + 5)))
		exit(EXIT_FAILURE);
	free(input);
	return (temp);
}

int		ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		save_env_sub(char *tab)
{
	int		i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i] != '$')
			ft_putchar_fd(tab[i], 1);
		else
			break ;
	}
	return (i);
}

void	save_env(char *tab, char **env, t_struct *glo)
{
	int		i;
	char	*tmp;

	i = save_env_sub(tab);
	if (!(tmp = ft_substr(tab, i + 1, ft_strlen(tab))))
		exit(EXIT_FAILURE);
	while (env[++i])
	{
		free(glo->env);
		if (ft_strnstr(env[i], tmp, ft_strlen(tmp)))
		{
			if (!(glo->env = ft_strdup(delete_char_right(env[i], '='))))
				exit(EXIT_FAILURE);
			free(tmp);
			return ;
		}
		else
		{
			if (!(glo->env = ft_strdup(" ")))
				exit(EXIT_FAILURE);
		}
	}
	free(tmp);
}

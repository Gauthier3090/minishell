/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:58:48 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/09 07:16:27 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_quotes_check_sub_simple(char *str, int i,
		int var, t_minishell *shell)
{
	int		k;
	int		j;

	j = i - 1;
	k = 0;
	while (str[i] && i < ((int)ft_strlen(str)))
	{
		if (str[i] == '\'' && shell->backs_input[i] == '0')
		{
			k = i;
			if (var < k && var > j)
				return (-1);
			else
			{
				j = 0;
				k = 0;
				break ;
			}
		}
		i++;
	}
	return (i);
}

int		ft_simple_quotes_check(char *str, int var, t_minishell *shell)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && shell->backs_input[i] == '0')
		{
			if (str[i + 1] && shell->backs_input[i + 1])
				i++;
			i = ft_quotes_check_sub_simple(str, i, var, shell);
			if (i == -1)
				return (TRUE);
			if (i >= (int)ft_strlen(shell->backs_input))
				break ;
		}
		i++;
	}
	return (FALSE);
}

int		ft_double_quotes_check(char *str, int var, t_minishell *shell)
{
	int		i;

	i = 0;
	while (str[i] && i < ((int)ft_strlen(str) - 1))
	{
		if (str[i + 2])
		{
			if (str[i] == '"' && i < ((int)ft_strlen(str) - 1) &&\
			shell->backs_input[i] == '0')
			{
				i++;
				i = ft_quotes_check_sub_double(str, i, var, shell);
				if (i == -1)
					return (TRUE);
			}
		}
		i++;
	}
	if (ft_simple_quotes_check(str, var, shell) == TRUE)
		return (TRUE);
	return (FALSE);
}

int		ft_struct_init(t_struct *glo, t_minishell *shell)
{
	char		buf[200];

	if (!(glo->env = ft_strdup("")))
		exit(EXIT_FAILURE);
	if (!(glo->arg = ft_strdup("")))
		exit(EXIT_FAILURE);
	if (getcwd(buf, 200) == NULL)
	{
		ft_put_errno(errno, shell);
		return (FALSE);
	}
	if (!(glo->oldpwd = ft_strdup(buf)))
		exit(EXIT_FAILURE);
	glo->cd_count = 0;
	glo->x = 0;
	glo->z = 0;
	glo->check = 0;
	glo->pipin = 0;
	glo->p = 0;
	shell->backs_tab = (char **)ft_calloc(3, sizeof(char *));
	if (!(glo->save_old_pwd = ft_strdup("")))
		exit(EXIT_FAILURE);
	return (TRUE);
}

char	**malloc_tab(char **tab)
{
	int		i;
	char	**new_tab;

	i = -1;
	if (!(new_tab = ft_calloc(ft_strlen_tab(tab) + 1, sizeof(char *))))
		exit(EXIT_FAILURE);
	while (tab[++i])
	{
		if (!(new_tab[i] = ft_strdup(tab[i])))
			exit(EXIT_FAILURE);
	}
	return (new_tab);
}

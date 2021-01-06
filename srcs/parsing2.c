/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:27:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/04 23:23:20 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		length_input_quote(char *str, int i)
{
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			break ;
		i++;
	}
	return (i);
}

int		length_input(char *str)
{
	int	length;
	int	i;

	length = 0;
	i = 0;
	while (str[i])
	{
		i = length_input_quote(str, i);
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '"')
				break ;
			i++;
		}
		i = length_input_quote(str, i);
		length++;
	}
	return (length);
}

void	input_to_tab_start_more(char *str, int *j, t_minishell *shell)
{
	shell->simple_quote_right = 0;
	shell->double_quote_right = 0;
	while (str[*j] && (shell->simple_quote_left != shell->simple_quote_right
	|| shell->double_quote_right != shell->double_quote_left))
	{
		if (str[*j] == '\'')
			shell->simple_quote_right++;
		else if (str[*j] == '"')
			shell->double_quote_right++;
		else
			break ;
		(*j)++;
	}
}

void	input_to_tab_start(char *str, int *j, t_minishell *shell)
{
	shell->simple_quote_left = 0;
	shell->double_quote_left = 0;
	while (str[*j])
	{
		if (str[*j] == '\'')
			shell->simple_quote_left++;
		else if (str[*j] == '"')
			shell->double_quote_left++;
		else
			break ;
		(*j)++;
	}
	while (str[*j])
	{
		if (str[*j] == '\'' || str[*j] == '"')
			break ;
		else
			shell->count++;
		(*j)++;
	}
	input_to_tab_start_more(str, j, shell);
}

char	**input_to_tab(char *str, int length, t_minishell *shell)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int		len;

	if (!(tab = (char **)ft_calloc(length + 1, sizeof(char *))))
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	len = -1;
	while (++i < length)
	{
		shell->count = 0;
		input_to_tab_start(str, &j, shell);
		if (!check_quote_close(shell))
			return (NULL);
		if (!(tab[i] = ft_calloc(shell->count + 1, sizeof(char))))
			exit(EXIT_FAILURE);
		k = -1;
		while (shell->count--)
			tab[i][++k] = str[++len];
	}
	return (tab);
}

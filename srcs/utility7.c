/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:38:46 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/05 15:01:56 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char		*create_backslash_quote(char *input, char *tmp, t_minishell *shell)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (input[++i])
	{
		if (shell->backs_input[i] != '0' && input[i] == '\'')
		{
			tmp[++j] = '"';
			tmp[++j] = '\'';
			tmp[++j] = '"';
		}
		else if (shell->backs_input[i] != '0' && input[i] == '"')
		{
			tmp[++j] = '\'';
			tmp[++j] = '"';
			tmp[++j] = '\'';
		}
		else
			tmp[++j] = input[i];
	}
	return (tmp);
}

char		*create_backs_input(char *input, char *backs_tmp, \
t_minishell *shell)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (input[++i])
	{
		if (shell->backs_input[i] != '0' && input[i] == '\'')
		{
			backs_tmp[++j] = '0';
			backs_tmp[++j] = '\'';
			backs_tmp[++j] = '0';
		}
		else if (shell->backs_input[i] != '0' && input[i] == '"')
		{
			backs_tmp[++j] = '0';
			backs_tmp[++j] = '\\';
			backs_tmp[++j] = '0';
		}
		else
			backs_tmp[++j] = shell->backs_input[i];
	}
	return (backs_tmp);
}

char		*check_backslash_quote(char *input, int i, t_minishell *shell)
{
	int		size;
	char	*tmp;
	char	*backs_tmp;

	size = 0;
	while (input[++i])
	{
		if (shell->backs_input[i] != '0'
		&& (input[i] == '"' || input[i] == '\''))
			size += 3;
		else
			size++;
	}
	if (!(tmp = ft_calloc(size + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	if (!(backs_tmp = ft_calloc(size + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	tmp = create_backslash_quote(input, tmp, shell);
	backs_tmp = create_backs_input(input, backs_tmp, shell);
	free(shell->backs_input);
	shell->backs_input = ft_strdup(backs_tmp);
	free(backs_tmp);
	free(input);
	return (tmp);
}

int			ft_quotes_check_sub_double(char *str, int i,
			int var, t_minishell *shell)
{
	int		k;
	int		j;

	j = i - 1;
	k = 0;
	while (str[i] && i < ((int)ft_strlen(str)))
	{
		if (str[i] == '"' && shell->backs_input[i] == '0')
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

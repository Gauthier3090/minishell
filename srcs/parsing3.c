/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:14:31 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/06 14:21:03 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	is_quote(char *input, t_minishell *shell)
{
	int	i;

	i = -1;
	shell->simple_quote = FALSE;
	shell->double_quote = FALSE;
	while (input[++i])
	{
		if (input[i] == '\'')
		{
			shell->simple_quote = TRUE;
			break ;
		}
		if (input[i] == '"')
		{
			shell->double_quote = TRUE;
			break ;
		}
	}
	if (input[i] == '\0')
		shell->double_quote = TRUE;
}

char	*add_quote(char *str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == c)
			len++;
	}
	if (!(new_str = ft_calloc(ft_strlen(str) + len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	j = -1;
	while (str[++i])
		new_str[++j] = str[i];
	while (len)
	{
		new_str[++j] = '\'';
		len--;
	}
	return (new_str);
}

char	*str_double_quote(t_minishell *shell, int i)
{
	int		j;
	char	*tmp;
	char	*variable;
	char	**arg;

	j = -1;
	tmp = ft_strdel(shell->tab_input[i], '"');
	variable = env_start(tmp, &j);
	if (*(&tmp[j]) != '\0')
	{
		if (!(arg = ft_split(&tmp[j], '$')))
			exit(EXIT_FAILURE);
		free(tmp);
		tmp = env_end(variable, arg, shell->env);
		variable = add_quote(tmp, '\'');
		free_tab(arg);
	}
	free(tmp);
	return (variable);
}

char	*str_simple_quote(t_minishell *shell, int i)
{
	int		j;
	char	*tmp;
	char	*variable;

	if (!(tmp = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	j = -1;
	while (shell->tab_input[i][++j])
	{
		if (!(tmp = ft_realloc(tmp, j + 1)))
			exit(EXIT_FAILURE);
		tmp[j] = shell->tab_input[i][j];
	}
	variable = ft_strdel(tmp, '\'');
	free(tmp);
	return (variable);
}

int		check_quote_close(t_minishell *shell)
{
	if (shell->simple_quote_left == shell->simple_quote_right
	&& shell->double_quote_left == shell->double_quote_right)
	{
		shell->count += (shell->simple_quote_left +
		shell->double_quote_left) * 2;
	}
	else
	{
		ft_putendl_fd("quote is not closed", 1);
		return (FALSE);
	}
	return (TRUE);
}

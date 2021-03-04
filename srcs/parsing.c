/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:40:50 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/04 15:31:15 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*parse_simple_quote(char *input, int *i)
{
	char	*tmp;
	char	*str;

	(*i)++;
	str = NULL;
	while (input[*i] && input[*i] != '\'')
	{
		tmp = str_not_env_simple_quotes(input, i);
		tmp ? str = realloc_str(str, tmp) : 0;
		free(tmp);
	}
	return (str);
}

char	*parse_double_quote(char *input, int *i, t_minishell *shell)
{
	char	*tmp;
	char	*str;

	(*i)++;
	str = NULL;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$' && (ft_voided_char(*i, shell->i, shell) == FALSE))
			tmp = str_env(input, i, shell->env, shell->ret);
		else if (ft_voided_char(*i, shell->i, shell) == TRUE)
			tmp = str_not_env_backslash(input, i);
		else
			tmp = str_not_env_double_quotes(input, i);
		tmp ? str = realloc_str(str, tmp) : 0;
		free(tmp);
	}
	return (str);
}

char	*parse_null_quote(char *input, int *i, t_minishell *shell)
{
	char	*tmp;
	char	*str;

	str = NULL;
	while (input[*i] && input[*i] != '"' && input[*i] != '\'')
	{
		if (input[*i] == '$' && (ft_voided_char(*i, shell->i, shell) == FALSE))
			tmp = str_env(input, i, shell->env, shell->ret);
		else
			tmp = str_not_env(input, i);
		tmp ? str = realloc_str(str, tmp) : 0;
		free(tmp);
	}
	(*i)--;
	return (str);
}

char	*parse_input_str(char *input, int *i, t_minishell *shell)
{
	char	*str;

	if (input[*i] == '"')
		str = parse_double_quote(input, i, shell);
	else if (input[*i] == '\'')
		str = parse_simple_quote(input, i);
	else
		str = parse_null_quote(input, i, shell);
	return (str);
}

char	*parse_input(char *input, t_minishell *shell)
{
	int		i;
	char	*str;
	char	*final_str;

	final_str = NULL;
	if (input)
	{
		i = 0;
		while ((size_t)i < ft_strlen(input))
		{
			str = parse_input_str(input, &i, shell);
			str ? final_str = realloc_str(final_str, str) : 0;
			free(str);
			i++;
		}
		!final_str ? final_str = empty_input(final_str) : 0;
		return (final_str);
	}
	return (NULL);
}

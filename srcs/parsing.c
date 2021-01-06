/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:40:50 by gpladet           #+#    #+#             */
/*   Updated: 2021/01/06 14:54:08 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_strdel(char *str, char c)
{
	int		i;
	int		len;
	char	*new_str;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != c)
			len++;
	}
	if (!(new_str = ft_calloc(len + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	len = -1;
	while (str[++i])
	{
		if (str[i] != c)
			new_str[++len] = str[i];
	}
	return (new_str);
}

char	*env_start(char *input, int *i)
{
	char	*str;
	int		j;

	if (!(str = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	j = 1;
	while (input[++(*i)] != '$' && input[*i])
	{
		if (!(str = ft_realloc(str, j + 1)))
			exit(EXIT_FAILURE);
		str[*i] = input[*i];
		j++;
	}
	return (str);
}

char	*found_env(char *input, int j, char **env)
{
	char	*tmp2;

	tmp2 = delete_char_right(env[j], '=');
	if (!(input = ft_realloc(input, ft_strlen(input) + ft_strlen(tmp2))))
		exit(EXIT_FAILURE);
	input = ft_strcat(input, tmp2);
	return (input);
}

char	*env_end(char *input, char **arg, char **env)
{
	char	*tmp;
	char	*str;
	int		i;
	int		j;

	i = -1;
	while (arg[++i])
	{
		str = ft_strdel(arg[i], '\'');
		j = -1;
		while (env[++j])
		{
			tmp = delete_char_left(env[j], '=');
			if (ft_strcmp(tmp, str) == 0)
				input = found_env(input, j, env);
			free(tmp);
		}
		free(str);
	}
	return (input);
}

char	*parse_input(t_minishell *shell, char *input, int free_input)
{
	char	*variable;
	int		i;

	if (input)
	{
		shell->len = length_input(input);
		if (!(shell->tab_input = input_to_tab(input, shell->len, shell)))
			return (NULL);
		shell->tmp_variable = ft_calloc(1, sizeof(char));
		i = -1;
		while (shell->tab_input[++i])
		{
			is_quote(shell->tab_input[i], shell);
			if (shell->double_quote)
				variable = str_double_quote(shell, i);
			else
				variable = str_simple_quote(shell, i);
			if (!(shell->tmp_variable = ft_realloc(shell->tmp_variable,
			ft_strlen(variable) + ft_strlen(shell->tmp_variable))))
				exit(EXIT_FAILURE);
			shell->tmp_variable = ft_strcat(shell->tmp_variable, variable);
			free(variable);
		}
		if (free_input)
			free(input);
		free_tab(shell->tab_input);
		return (shell->tmp_variable);
	}
	return (NULL);
}

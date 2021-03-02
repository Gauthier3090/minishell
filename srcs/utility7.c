/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:38:46 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/02 14:43:27 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char		*ft_backs_whitespace(t_minishell *shell, char *str)
{
	char	*temp;
	int		i;

	i = 0;
	while (shell->white > 0)
	{
		shell->white--;
		i++;
	}
	if (!(temp = ft_substr(str, i, ft_strlen(str) - i)))
		exit(EXIT_FAILURE);
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

void		init_shell_arg(t_minishell *shell)
{
	if (shell->variable && shell->value)
	{
		if (!(shell->arg = ft_strjoin(shell->variable, shell->value)))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(shell->arg = ft_strdup(shell->variable)))
			exit(EXIT_FAILURE);
	}
}

int			ft_builtins(t_minishell *shell, t_struct *glo)
{
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		echo(shell);
	else if (ft_strcmp(shell->tab[0], "exit") == 0)
	{
		if (!(exit_shell(shell->tab, shell)))
			return (FALSE);
	}
	else if (ft_strcmp(shell->tab[0], "env") == 0)
		ft_env(shell->tab, shell->env, shell);
	else if (ft_strcmp(shell->tab[0], "export") == 0)
		export(shell);
	else if (ft_strcmp(shell->tab[0], "unset") == 0)
		unset(shell);
	else if (ft_strcmp(shell->tab[0], "cd") == 0)
		ft_cd(shell->input, shell->env, glo, shell);
	else if (ft_strcmp(shell->tab[0], "pwd") == 0)
		ft_pwd(shell);
	else
		ft_exec(shell, glo);
	return (TRUE);
}

char		*create_backslash_quote(char *input, char *tmp)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (input[++i])
	{
		if (input[i] == '\\' && input[i + 1] == '\'')
		{
			tmp[++j] = '"';
			tmp[++j] = '\'';
			tmp[++j] = '"';
			i++;
		}
		else if (input[i] == '\\' && input[i + 1] == '"')
		{
			tmp[++j] = '\'';
			tmp[++j] = '"';
			tmp[++j] = '\'';
			i++;
		}
		else
			tmp[++j] = input[i];
	}
	return (tmp);
}

char		*check_backslash_quote(char *input)
{
	int		i;
	int		size;
	char	*tmp;

	i = -1;
	size = 0;
	while (input[++i])
	{
		if (input[i] == '\\' && (input[i + 1] == '"' || input[i + 1] == '\''))
		{
			size += 3;
			i++;
		}
		else
			size++;
	}
	if (!(tmp = ft_calloc(size + 1, sizeof(char))))
		exit(EXIT_FAILURE);
	tmp = create_backslash_quote(input, tmp);
	free(input);
	return (tmp);
}

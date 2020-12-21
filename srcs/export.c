/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:40:35 by gpladet           #+#    #+#             */
/*   Updated: 2020/12/21 22:25:23 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*research_env(char **env, char *str_research)
{
	int		i;
	int		count;
	char	*tmp;
	char	*str;

	if (!(str = ft_calloc(1, 2 * sizeof(char))))
		exit(EXIT_FAILURE);
	i = -1;
	count = 0;
	while (str_research[++i])
	{
		if (str_research[i] != '$')
		{
			if (!(str = ft_realloc(str, count + 1)))
				exit(EXIT_FAILURE);
			str[i] = str_research[i];
			count++;
		}
		else
			break ;
	}
	if (!(tmp = ft_substr(str_research, i + 1, ft_strlen(str_research))))
		exit(EXIT_FAILURE);
	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			tmp = delete_char(env[i], '=');
			if (!(str = ft_realloc(str, ft_strlen(tmp) + ft_strlen(str))))
				exit(EXIT_FAILURE);
			str = ft_strcat(str, tmp);
			return (str);
		}
	}
	free(tmp);
	if (str[0] == '\0')
		return (ft_strdup("''"));
	return (str);
}

int		variable_exist(char **env, char *str)
{
	int	i;
	int	j;
	int	length;

	i = -1;
	length = ft_strlen(str);
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (!ft_strncmp(env[i], str, j) && !ft_strncmp(env[i], str, length))
			return (i);
	}
	return (-1);
}

void	create_variable(t_minishell *shell, char **arg, int i)
{
	char	*str;
	char	*tmp;
	int		j;
	int		env;

	if (!arg[1])
	{
		if (!(tmp = ft_strdup(arg[0])))
			exit(EXIT_FAILURE);
		if (!(tmp = ft_realloc(tmp, ft_strlen(tmp) + 5)))
			exit(EXIT_FAILURE);
		tmp = ft_strcat(tmp, "=''");
	}
	else
	{
		env = FALSE;
		j = -1;
		while (arg[1][++j])
		{
			if (arg[1][j] == '$')
			{
				env = TRUE;
				if (!(tmp = ft_strdup(arg[0])))
					exit(EXIT_FAILURE);
				str = research_env(shell->env, arg[1]);
				if (!(tmp = ft_realloc(tmp, ft_strlen(tmp) +
				ft_strlen(str) + 2)))
					exit(EXIT_FAILURE);
				tmp = ft_strcat(tmp, "=");
				tmp = ft_strcat(tmp, str);
				break ;
			}
		}
		if (!env)
		{
			if (!(tmp = ft_strdup(shell->tab[i])))
				exit(EXIT_FAILURE);
		}
	}
	str = tabtostr(shell->env);
	if (!(str = ft_realloc(str, ft_strlen(str) + ft_strlen(tmp) + 2)))
		exit(EXIT_FAILURE);
	str = ft_strcat(str, "\n");
	str = ft_strcat(str, tmp);
	if (!(shell->env = ft_split(str, '\n')))
		exit(EXIT_FAILURE);
	free(str);
	free(tmp);
}

void	create_env_variable(t_minishell *shell, int i)
{
	char	**arg;
	char	*tmp;
	int		index;
	int		j;

	shell->tab[i] = ft_whitespace(shell->tab[i]);
	if (!(arg = ft_split(shell->tab[i], '=')))
		exit(EXIT_FAILURE);
	if ((index = variable_exist(shell->env, arg[0])) != -1)
	{
		free(shell->env[index]);
		if (arg[1])
		{
			j = -1;
			while (arg[1][++j])
			{
				if (arg[1][j] == '$')
				{
					tmp = research_env(shell->env, arg[1]);
					if (!(arg[0] = ft_realloc(arg[0], 2 + ft_strlen(tmp))))
						exit(EXIT_FAILURE);
					arg[0] = ft_strcat(arg[0], "=");
					arg[0] = ft_strcat(arg[0], tmp);
					free(tmp);
					if (!(shell->env[index] = ft_strdup(arg[0])))
						exit(EXIT_FAILURE);
					free_tab(arg);
					return ;
				}
			}
			if (!(shell->env[index] = ft_strdup(shell->tab[i])))
				exit(EXIT_FAILURE);
		}
	}
	else if (arg[0][0] == '$')
		ft_putendl_fd("variable", 1);
	else
		create_variable(shell, arg, i);
	free_tab(arg);
}

void	export(t_minishell *shell)
{
	int	i;

	if (ft_strlen_tab(shell->tab) == 1)
		sorting_env(shell->env, ft_strlen_tab(shell->env));
	i = 0;
	while (shell->tab[++i])
	{
		if (shell->tab[i][0] == '=')
		{
			ft_putendl_fd("minishell: bad assignment", 2);
			exit(EXIT_FAILURE);
		}
		create_env_variable(shell, i);
	}
}

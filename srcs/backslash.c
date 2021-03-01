/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:41:11 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/01 14:31:59 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_double_quotes_voided(char *str, t_minishell *shell, int x, int i)
{
	if (str[i] == '\\' && shell->backs_tab[x][i] == '0' && \
	ft_simple_quotes_check(/*shell, */shell->tab[x], i) == FALSE &&\
	str[i + 1] == '"')
	{
		shell->backs_tab[x][i] = str[i];
		while (str[i])
		{
			str[i] = str[i + 1];
			i++;
		}
		i = 0;
		return (TRUE);
	}
	return (FALSE);
}

int		ft_simple_quotes_voided(char *str, t_minishell *shell, int x, int i)
{
	if (str[i] == '\\' && shell->backs_tab[x][i] == '0' && \
	ft_double_quotes_check(/*shell, */shell->tab[x], i) == FALSE &&\
	str[i + 1] == '\'')
	{
		shell->backs_tab[x][i] = str[i];
		while (str[i])
		{
			str[i] = str[i + 1];
			i++;
		}
		i = 0;
		return (TRUE);
	}
	return (FALSE);
}

int			ft_voided_char(int i, int x, t_minishell *shell)
{
	if (shell->backs_tab[x][i] && shell->backs_tab[x][i] != '0')
		return (TRUE);
	/*else*/
		return (FALSE);
}

char		*ft_backzero(char *str)
{
	int		x;

	x = 0;
	while (str[x])
	{
		str[x] = '0';
		x++;
	}
	x = 0;
	while (str[x])
	{
		/*ft_putchar_fd(str[x], 1);*/
		x++;
	}
	return (str);
}

char		*ft_backslash(char *str, t_minishell *shell, int x)
{
	int		i;

	i = 0;
	shell->backs_tab[x] = ft_backzero(shell->backs_tab[x]);
	while (str[i])
	{
		if (str[i] == '\\' && shell->backs_tab[x][i] == '0')
		{
			if (ft_double_quotes_voided(str, shell, x, i) == TRUE)
			{
				shell->backs_tab[x][i] = str[i];
				i = 0;
			}
			else if (ft_simple_quotes_voided(str, shell, x, i) == TRUE)
			{
				shell->backs_tab[x][i] = str[i];
				i = 0;
			}
			else if (ft_simple_quotes_check(/*shell, */shell->tab[x], i) == TRUE)
			{
				shell->backs_tab[x][i] = str[i];
				i = 0;
			}
			else if (ft_double_quotes_check(/*shell, */shell->tab[x], i) == FALSE)
			{
				shell->backs_tab[x][i] = str[i];
				while (str[i])
				{
					str[i] = str[i + 1];
					i++;
				}
				i = 0;
			}
			else if (ft_double_quotes_check(/*shell, */shell->tab[x], i) == TRUE\
			&& (str[i + 1] == '$' || str[i + 1] == '\\') &&\
			ft_simple_quotes_check(/*shell, */shell->tab[x], i) == FALSE)
			{
				shell->backs_tab[x][i] = str[i];
				while (str[i])
				{
					str[i] = str[i + 1];
					i++;
				}
				i = 0;
			}
			else
			{
				shell->backs_tab[x][i] = str[i];
				i = 0;
			}
		}
		i++;
	}
	return (str);
}

void		ft_tab_dup(t_minishell *shell)
{
	int		i;

	i = 0;
	if (!(shell->backs_tab = split_input(shell->input)))
		exit(EXIT_FAILURE);
	shell->backs_input = ft_strdup(shell->input);
	shell->input = ft_backslash_input(shell->input, shell);
	while (shell->backs_tab[i])
	{
		shell->tab[i] = ft_backslash(shell->tab[i], shell, i);
		/*ft_putstr_fd("shell->backs_tab[i]", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(" === ", 1);*/
		/*ft_putstr_fd(" backtab=", 1);
		ft_putstr_fd(shell->backs_tab[i], 1);
		ft_putstr_fd("\n", 1);*/
		/*ft_putstr_fd(" tab=", 1);
		ft_putstr_fd(shell->tab[i], 1);
		ft_putstr_fd("\n", 1);*/
		i++;
	}
}

int			ft_voided_char_input(int i, t_minishell *shell)
{
	/*ft_putstr_fd("shell->backs_input = ", 1);
	ft_putstr_fd(shell->backs_input, 1);*/
	if (shell->backs_input[i] && shell->backs_input[i] != '0')
		return (TRUE);
	/*else*/
		return (FALSE);
}

char		*ft_backslash_input(char *str, t_minishell *shell)
{
	int		i;

	i = 0;
	shell->backs_input = ft_backzero(shell->backs_input);
	while (str[i])
	{
		if (str[i] == '\\' && shell->backs_input[i] == '0')
		{
			/*if (ft_double_quotes_voided(str, shell, 0, i) == TRUE)
			{
				shell->backs_input[i] = str[i];
				i = 0;
			}
			else if (ft_simple_quotes_voided(str, shell, 0, i) == TRUE)
			{
				shell->backs_input[i] = str[i];
				i = 0;
			}
			else */if (ft_simple_quotes_check(/*shell, */shell->input, i) == TRUE)
			{
				shell->backs_input[i] = str[i];
				i = 0;
			}
			else if (ft_double_quotes_check(/*shell, */shell->input, i) == FALSE)
			{
				shell->backs_input[i] = str[i];
				while (str[i])
				{
					str[i] = str[i + 1];
					i++;
				}
				i = 0;
			}
			else if (ft_double_quotes_check(/*shell, */shell->input, i) == TRUE\
			&& (str[i + 1] == '$' || str[i + 1] == '\\') &&\
			ft_simple_quotes_check(/*shell, */shell->input, i) == FALSE)
			{
				shell->backs_input[i] = str[i];
				while (str[i])
				{
					str[i] = str[i + 1];
					i++;
				}
				i = 0;
			}
			else
			{
				shell->backs_input[i] = str[i];
				i = 0;
			}
		}
		i++;
	}
	return (str);
}

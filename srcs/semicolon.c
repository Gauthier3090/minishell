/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:17:08 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/21 17:16:37 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_simple_quotes_check(t_minishell *shell, t_struct *glo)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (shell->input && shell->input[i])
	{
		if (shell->input[i] == '\'')
		{
			j = i;
			i++;
			while (shell->input && shell->input[i])
			{
				if (shell->input[i] == '\'')
				{
					k = i;
					if (glo->i < k && glo->i > j)
						return (TRUE);
					else
					{
						i = k + 1;
						j = 0;
						k = 0;
						break ;
					}
				}
				i++;
			}
		}
		i++;
	}
	return (FALSE);
}

int		ft_double_quotes_check(t_minishell *shell, t_struct *glo)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (shell->input && shell->input[i])
	{
		if (shell->input[i] == '"')
		{
			j = i;
			i++;
			while (shell->input && shell->input[i])
			{
				if (shell->input[i] == '"')
				{
					k = i;
					if (glo->i < k && glo->i > j)
					{
						/*ft_putstr_fd("j = ", 1);
						ft_putnbr_fd(j, 1);
						ft_putstr_fd("\nk = ", 1);
						ft_putnbr_fd(k, 1);*/
						return (TRUE);
					}
					else
					{
						i = k + 1;
						j = 0;
						k = 0;
						/*ft_putstr_fd("\nbreak\n", 1);*/
						break ;
					}
				}
				i++;
			}
		}
		i++;
	}
	if (ft_simple_quotes_check(shell, glo) == TRUE)
		return (TRUE);
	/*ft_putstr_fd("quit = ", 1);*/
	return (FALSE);
}

void	ft_loop_sub(t_minishell *shell, t_struct *glo, int i)
{
	int		x;
	/*char	*temp;*/

	x = 0;
	glo->check = 2;
	/*while (shell->tab && shell->tab[x])
	{
	ft_putstr_fd("\nshell->tab[x] = ", 1);
		ft_putstr_fd(shell->tab[x], 1);
		x++;
	}
	x = 0;*/
	free(shell->input);
	/*ft_putstr_fd("\ni = ", 1);
	ft_putnbr_fd(i, 1);*/
	if (!(shell->input = ft_strdup(glo->forked_tab[i])))
		exit(EXIT_FAILURE);
	free_tab(shell->tab);
	while (shell->input[x])
		x++;
	if (!(shell->tab = split_input(shell->input)))
			exit(EXIT_FAILURE);
	/*ft_putstr_fd("\nshell->input = ", 1);
	ft_putstr_fd(shell->input, 1);*/
	/*temp = ft_substr(shell->input, 0, x);
	if (!(shell->tab = ft_split(temp, ' ')))
		exit(EXIT_FAILURE);
	free(temp);*/
	glo->x--;
	shell->input = ft_whitespace(shell->input);
	/*ft_putstr_fd("input_semi = ", 1);
	ft_putstr_fd(shell->input, 1);*/
	shell->i = 0;
	ft_loop_main(shell, glo);
}

int		ft_semicolon_sub(t_minishell *shell, t_struct *glo)
{
	int		i;
	int		x;
	int		z;

	i = 1;
	x = 0;
	z = 0;
	glo->forked_tab = malloc((glo->x + 2) * sizeof(char*));
	while (x < glo->x)
	{
		/*ft_putstr_fd("\nx = ", 1);
		ft_putnbr_fd(glo->semi[x], 1);*/
		glo->forked_tab[x] = ft_substr(shell->input, z, (glo->semi[x]) - z);
		z = glo->semi[x] + 1;
		/*ft_putstr_fd("\nz = ", 1);
		ft_putnbr_fd(z, 1);*/
		x++;
	}
	glo->forked_tab[x] = ft_substr(shell->input, z, ft_strlen(shell->input) - z);
	glo->forked_tab[x + 1] = NULL;
	x = 0;
	/*while (glo->forked_tab && glo->forked_tab[x])
	{
		ft_putstr_fd(" \nglo->forked_tab ", 1);
		ft_putnbr_fd(x, 1);
		ft_putstr_fd(glo->forked_tab[x], 1);
		x++;
	}
	x = 0;*/
	while (shell->input[ft_strlen(shell->input) - i] == ' ' || shell->input[ft_strlen(shell->input) - i] == ';')
	{
		if (shell->input[ft_strlen(shell->input) - i] == ';')
			x = 1;
		i++;
	}
	i = 0;
	while (glo->x > -1)
	{
		if (glo->x == 0 && x == 1)
			break ;
		ft_loop_sub(shell, glo, i);
		i++;
	}
	glo->check = 0;
	glo->x = 0;
	glo->forked_tab ? free_tab(glo->forked_tab) : 0;
	return (FALSE);
}

int		ft_check_double_char(t_minishell *shell, t_struct *glo, char c)
{
	int		y;

	while (shell->input[glo->i])
	{
		if ((shell->input[glo->i] == c) && (ft_double_quotes_check(shell, glo) == FALSE))
		{
			glo->semi[glo->x] = glo->i;
			glo->x++;
			glo->check = 1;
			y = 1;
			while (shell->input && (shell->input[glo->i + y] == ' ' ||
				shell->input[glo->i + y] == '\t' || \
				shell->input[glo->i + y] == '\v'))
				y++;
			if (shell->input[glo->i + y] == c)
			{
				ft_putstr_fd("bash: syntax error near unexpected token `", 1);
				ft_putchar_fd(c, 1);
				ft_putstr_fd("'\n", 1);
				shell->variable ? free(shell->variable) : 0;
				shell->value ? free(shell->value) : 0;
				shell->variable = NULL;
				shell->value = NULL;
				glo->x = 0;
				glo->check = 0;
				return (FALSE);
			}
		}
		glo->i++;
	}
	/*ft_putstr_fd("quit check \n ", 1);*/
	return (TRUE);
}


int		ft_semicolon(t_minishell *shell, t_struct *glo)
{
	/*ft_putstr_fd("IN SEMI ", 1);*/
	glo->i = 0;
	if (glo->check == 2)
		return (TRUE);
	while (shell->input && (shell->input[glo->i] == ' ' || \
	shell->input[glo->i] == '\t' || shell->input[glo->i] == '\v'))
		glo->i++;
	if (shell->input[glo->i] == ';')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `;'\n", 1);
		return (FALSE);
	}
	if (ft_check_double_char(shell, glo, ';') == FALSE)
		return (FALSE);
	if (glo->x == 0)
		return (TRUE);
	if (ft_semicolon_sub(shell, glo) == FALSE)
		return (FALSE);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:35:00 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/02 22:21:05 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		ft_check_double_char_sub(t_minishell *shell, t_struct *glo)
{
	shell->ret = ft_putstr_error("bash: syntax error near \
	unexpected token `;'\n", NULL, 2);
	shell->variable ? free(shell->variable) : 0;
	shell->value ? free(shell->value) : 0;
	shell->arg ? free(shell->arg) : 0;
	shell->arg = NULL;
	shell->variable = NULL;
	shell->value = NULL;
	glo->x = 0;
	glo->check = 0;
}

void		ft_semico_malloc(t_minishell *shell, t_struct *glo)
{
	int		z;
	int		x;

	x = 0;
	z = 0;
	glo->semico = malloc((glo->x + 2) * sizeof(char*));
	while (x < glo->x)
	{
		glo->semico[x] = ft_substr(shell->input, z, (glo->semi[x]) - z);
		z = glo->semi[x] + 1;
		x++;
	}
	glo->semico[x] = ft_substr(shell->input, z, ft_strlen(shell->input) - z);
	glo->semico[x + 1] = NULL;
}

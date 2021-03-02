/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:35:00 by ldavids           #+#    #+#             */
/*   Updated: 2021/03/02 14:27:53 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void		ft_check_double_char_sub(t_minishell *shell, t_struct *glo)
{
	shell->ret = ft_putstr_error(\
	"bash: syntax error near unexpected token `;'\n", NULL, 2);
	shell->variable ? free(shell->variable) : 0;
	shell->value ? free(shell->value) : 0;
	shell->arg ? free(shell->arg) : 0;
	shell->arg = NULL;
	shell->variable = NULL;
	shell->value = NULL;
	glo->x = 0;
	glo->check = 0;
}

void		ft_init_semico_malloc(t_minishell *shell, t_struct *glo)
{
	if (!(glo->semico = malloc((glo->x + 2) * sizeof(char*))))
		exit(EXIT_FAILURE);
	if (!(shell->semi_backs_tab = malloc((glo->x + 2) * sizeof(char*))))
		exit(EXIT_FAILURE);
}

void		ft_semico_malloc(t_minishell *shell, t_struct *glo)
{
	int		z;
	int		x;

	ft_init_semico_malloc(shell, glo);
	x = 0;
	z = 0;
	while (x < glo->x)
	{
		if (!(glo->semico[x] = ft_substr(shell->input, z, (glo->semi[x]) - z)))
			exit(EXIT_FAILURE);
		if (!(shell->semi_backs_tab[x] = ft_substr(shell->backs_input, z,
		(glo->semi[x]) - z)))
			exit(EXIT_FAILURE);
		z = glo->semi[x] + 1;
		x++;
	}
	if (!(glo->semico[x] = ft_substr(shell->input, z, \
	ft_strlen(shell->input) - z)))
		exit(EXIT_FAILURE);
	if (!(shell->semi_backs_tab[x] = ft_substr(shell->backs_input, z, \
		ft_strlen(shell->backs_input) - z)))
		exit(EXIT_FAILURE);
	shell->semi_backs_tab[x + 1] = NULL;
	glo->semico[x + 1] = NULL;
}

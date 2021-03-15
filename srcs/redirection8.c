/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:21:57 by gpladet           #+#    #+#             */
/*   Updated: 2021/03/15 16:00:11 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_redirection_pipe(t_minishell *shell, t_struct *glo)
{
	if (!shell->redirection_read)
		shell->str = realloc_str(shell->str, "| grep -q \"\"");
	shell->input ? free(shell->input) : 0;
	shell->input = ft_strdup(shell->str);
	ft_putendl_fd(shell->input, 1);
	free(shell->str);
	ft_pipe_main(shell, glo);
	ft_free_args(shell);
	free_tab(shell->pipe_tab);
	shell->delete_redir = FALSE;
}

int		ft_redirection_backslash(t_minishell *shell)
{
	int	i;

	if (!check_redirection(shell->input))
		return (TRUE);
	i = -1;
	while (shell->input[++i])
	{
		if ((shell->input[i] == '>' || shell->input[i] == '<')
		&& ft_voided_char_input(i, shell))
			return (TRUE);
	}
	return (FALSE);
}

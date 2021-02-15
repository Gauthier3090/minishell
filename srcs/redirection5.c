/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:56:39 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/15 17:10:03 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_redirection_command_append(int append)
{
	char	*command;

	if (!append)
	{
		if (!(command = ft_strdup("tee ")))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(command = ft_strdup("tee -a ")))
			exit(EXIT_FAILURE);
	}
	return (command);
}

char	**ft_create_command_pipe(char **redir_tab, int redirection_read)
{
	int		i;
	char	*command;

	i = -1;
	while (++i < ft_strlen_tab(redir_tab))
	{
		if (i < ft_strlen_tab(redir_tab) - 1)
		{
			if (!(command = ft_strdup(" | ")))
				exit(EXIT_FAILURE);
			redir_tab[i] = realloc_str(redir_tab[i], command);
		}
		else if (!redirection_read)
		{
			if (!(command = ft_strdup(" | grep -q \"\"")))
				exit(EXIT_FAILURE);
			redir_tab[i] = realloc_str(redir_tab[i], command);
		}
		free(command);
		command = NULL;
	}
	return (redir_tab);
}

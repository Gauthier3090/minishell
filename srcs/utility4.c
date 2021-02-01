/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:15:29 by ldavids           #+#    #+#             */
/*   Updated: 2021/02/01 15:50:14 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

void	quotes_close(int *i, char c, t_minishell *shell)
{
	if (shell->input[*i] == c)
	{
		shell->quote++;
		while (shell->input[++(*i)])
		{
			if (shell->input[*i] == c)
			{
				shell->quote++;
				break ;
			}
		}
	}
}

int		check_quotes_close(t_minishell *shell)
{
	int	i;

	shell->quote = 0;
	i = -1;
	while ((size_t)++i < ft_strlen(shell->input))
	{
		if (shell->input[i] == '\'')
			quotes_close(&i, '\'', shell);
		if (shell->input[i] == '"')
			quotes_close(&i, '"', shell);
	}
	if (shell->quote % 2 != 0)
		return (0);
	return (1);
}

char	*realloc_str(char *dest, char *src)
{
	if (!(dest = ft_realloc(dest, ft_strlen(dest) + ft_strlen(src) + 1)))
		exit(EXIT_FAILURE);
	dest = ft_strcat(dest, src);
	return (dest);
}

void	ft_close_fd(t_struct *glo, int *pipefd)
{
	int		j;

	j = 0;
	while (j < 2 * glo->z)
	{
		if (close(pipefd[j]) < 0)
		{
			ft_put_errno(errno);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

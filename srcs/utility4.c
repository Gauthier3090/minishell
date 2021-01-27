/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:15:29 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/27 15:04:02 by ldavids          ###   ########.fr       */
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

int		quotes_close(int *i, char c, char c2, t_minishell *shell)
{
	if (shell->input[*i] == c)
	{
		shell->quote++;
		while (shell->input[++(*i)])
		{
			if (shell->input[*i] == c2)
				shell->quote2++;
			else if (shell->input[*i] == c)
			{
				shell->quote++;
				if (shell->quote2 % 2 != 0)
					return (0);
				else
					break ;
			}
		}
	}
	return (1);
}

int		check_quotes_close(t_minishell *shell)
{
	int	i;

	shell->quote = 0;
	shell->quote2 = 0;
	i = -1;
	while ((size_t)++i < ft_strlen(shell->input))
	{
		if (shell->input[i] == '\'')
		{
			if (!quotes_close(&i, '\'', '"', shell))
				return (0);
		}
		if (shell->input[i] == '"')
		{
			if (!quotes_close(&i, '"', '\'', shell))
				return (0);
		}
	}
	if (shell->quote % 2 != 0 || shell->quote2 % 2 != 0)
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

void		ft_free_exec(t_struct *glo, char **bin, char *path)
{
	free_tab(glo->tab);
	free_tab(glo->tab2);
	free_tab(bin);
	free(path);
	if (glo->pipin == 1)
		exit(EXIT_SUCCESS);
}

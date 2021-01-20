/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:15:29 by ldavids           #+#    #+#             */
/*   Updated: 2021/01/20 14:55:14 by ldavids          ###   ########.fr       */
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

int		quotes_close(char *str, int *i, char c, char c2, int *quote, int *quote2)
{
	if (str[*i] == c)
	{
		(*quote)++;
		while (str[++(*i)])
		{
			if (str[*i] == c2)
				(*quote2)++;
			else if (str[*i] == c)
			{
				(*quote)++;
				if (*quote2 % 2 != 0)
					return (0);
				else
					break ;
			}
		}
	}
	return (1);
}

int		check_quotes_close(char *str)
{
	int	i;
	int	quote;
	int	quote2;

	quote = 0;
	quote2 = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (!quotes_close(str, &i, '\'', '"', &quote, &quote2))
				return (0);
		}
		if (str[i] == '"')
		{
			if (!quotes_close(str, &i, '"', '\'', &quote, &quote2))
				return (0);
		}
	}
	if (quote % 2 != 0 || quote2 % 2 != 0)
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

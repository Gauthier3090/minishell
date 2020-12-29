/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:21:04 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/29 16:25:31 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_whitespace(char *input)
{
	char	*temp;
	int		i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t' || input[i] == '\v'
	|| input[i] == '\f' || input[i] == '\n'))
		i++;
	if (!(temp = ft_substr(input, i, ft_strlen(input) - i)))
		exit(EXIT_FAILURE);
	free(input);
	return (temp);
}

int		ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	save_env(char *tab, char **env, t_struct *glo)
{
	int		i;
	char	*tmp;

	i = -1;
	while (tab[++i])
	{
		if (tab[i] != '$')
			ft_putchar_fd(tab[i], 1);
		else
			break ;
	}
	tmp = ft_substr(tab, i + 1, ft_strlen(tab));
	while (env[++i])
	{
		free(glo->env);
		if (ft_strnstr(env[i], tmp, ft_strlen(tmp)))
		{
			glo->env = ft_strdup(delete_char_right(env[i], '='));
			free(tmp);
			return ;
		}
		else
			glo->env = ft_strdup(" ");
	}
	free(tmp);
}

int		ft_struct_init(t_struct *glo)
{
	char		buf[200];

	glo->env = ft_strdup("");
	glo->arg = ft_strdup("");
	if (getcwd(buf, 200) == NULL)
	{
		ft_putendl_fd(strerror(errno), 1);
		return (FALSE);
	}
	glo->oldpwd = ft_strdup(buf);
	glo->cd_count = 0;
	glo->x = 0;
	glo->check = 0;
	return (TRUE);
}

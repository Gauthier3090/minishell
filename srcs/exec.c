/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:42:42 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/21 17:44:56 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"


int		ft_exec(t_minishell *minishell)
{
char		**arg;
char		**arg2;
int			i;

i = 0;
if (!(arg = ft_split(minishell->input, ' ')))
		exit(EXIT_FAILURE);
while (arg[i])
	i++;
if (!(arg2 = ft_calloc(sizeof(char *), i + 3)))
		exit(EXIT_FAILURE);
if ((ft_strcmp(arg[0], "bash") == 0) || (ft_strcmp(arg[0], "sh") == 0))
{
	if (!(arg2[0] = ft_strdup("/bin/bash")))
		exit(EXIT_FAILURE);
}
/*else if (ft_strncmp(arg[0], "./", 2) == 0)
{*/
	if (!(arg2[0] = ft_strdup(arg[0])))
	exit(EXIT_FAILURE);
/*}
else
	return (0);*/
i = 1;
while (arg[i])
{
	if (!(arg2[i] = ft_strdup(arg[i])))
		exit(EXIT_FAILURE);
	i++;
}
arg2[++i] = NULL;
i = 0;
while (arg2[i])
{
	ft_putstr_fd(arg2[i++], 1);
	ft_putstr_fd("\n", 1);
}
if (execve(arg2[0], arg2, minishell->env) == -1)
{
	ft_putstr_fd(strerror(errno), 1);
	write(1, "\n", 1);
}
return (1);
}


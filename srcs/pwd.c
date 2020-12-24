/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 22:10:02 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/24 15:40:40 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_pwd(char *input)
{
	int				i;
	char			*buf;

	i = 3;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
			return ;
		i++;
	}
	if ((buf = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd(strerror(errno), 1);
	else
		ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
}

void	ft_ls(char *input)
{
	DIR				*mydir;
	struct dirent	*entry;
	char			*buf;
	int				i;

	i = 2;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
			return ;
		i++;
	}
	buf = getcwd(NULL, 0);
	if (!(mydir = opendir(buf)))
		ft_errno_putstr(errno);
	errno = 0;
	while ((entry = readdir(mydir)) != NULL)
		ft_ls_sub(entry);
	if (errno != 0)
		ft_errno_putstr(errno);
	closedir(mydir);
	free(buf);
	ft_ls_files();
}

void	ft_ls_files(void)
{
	DIR				*mydir;
	struct dirent	*entry;
	char			*buf;

	buf = getcwd(NULL, 0);
	if (!(mydir = opendir(buf)))
		ft_errno_putstr(errno);
	errno = 0;
	while ((entry = readdir(mydir)) != NULL)
	{
		if (entry->d_type > 5)
		{
			ft_putstr_fd(entry->d_name, 1);
			printf("\n");
		}
	}
	if (errno != 0)
		ft_errno_putstr(errno);
	free(buf);
	closedir(mydir);
}

void	ft_errno_putstr(int errnumb)
{
	ft_putstr_fd(strerror(errnumb), 1);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_ls_sub(struct dirent	*entry)
{
	if (entry->d_type < 5)
	{
		ft_putstr_fd(GREEN, 1);
		ft_putstr_fd(entry->d_name, 1);
		ft_putstr_fd(RESET, 1);
		printf("\n");
	}
}

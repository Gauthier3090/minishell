/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpladet <gpladet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:12:11 by gpladet           #+#    #+#             */
/*   Updated: 2021/02/15 15:28:19 by gpladet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define PATH_MAX 4096
# define CYAN "\e[38;5;123m"
# define GREEN "\e[38;5;28m"
# define RESET "\e[0m"
# define TRUE 1
# define FALSE 0
# define ERROR_REDIRECTION_RIGHT "minishell: parse error near `>>'\n"
# define ERROR_REDIRECTION_LEFT "minishell: parse error near `<'\n"
# define ERROR_REDIRECTION_SIMPLE "minishell: parse error near `>'\n"
# define ERROR_REDIRECTION_EMPTY "minishell: parse error near `\\n'\n"

#endif

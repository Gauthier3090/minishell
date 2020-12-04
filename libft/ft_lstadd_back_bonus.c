/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:31:12 by ldavids           #+#    #+#             */
/*   Updated: 2019/10/31 15:31:14 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (alst == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	ft_lstlast(*alst)->next = new;
}

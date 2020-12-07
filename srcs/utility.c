/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:21:04 by ldavids           #+#    #+#             */
/*   Updated: 2020/12/07 16:24:28 by ldavids          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char*	ft_whitespace(char *input)
{
char*	temp;
int		i;

i = 0;
while (input[i] && (input[i] == ' ' || input[i] == '\t' || input[i] == '\v' || input[i] == '\f' || input[i] == '\n'))
i++;
temp = ft_substr(input, i, ft_strlen(input) - i);
free(input);
return (temp);
}

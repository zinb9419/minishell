/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:25:37 by ziloughm          #+#    #+#             */
/*   Updated: 2022/09/13 21:42:11 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_calloc(size_t n, size_t s)
{
	char	*p;
	size_t	i;

	p = 0;
	i = 0;
	p = malloc(n * s);
	if (!p)
		return (0);
	ft_bzero(p, n * s);
	return (p);
}

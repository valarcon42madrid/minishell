/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:12:11 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:12:12 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		cont;
	char		*a;

	a = (char *)s;
	cont = 1;
	while (cont <= n)
	{
		a[cont - 1] = 0;
		cont++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:16:53 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/26 18:31:50 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		cont;
	char		*dest;
	char		*source;
	char		ch;

	cont = 0;
	ch = (unsigned char)c;
	dest = (char *)dst;
	source = (char *)src;
	if (n != 0)
	{
		while (n--)
		{
			dest[cont] = source[cont];
			if (source[cont] == ch)
				return (&dst[cont + 1]);
			cont++;
		}
	}
	return (0);
}

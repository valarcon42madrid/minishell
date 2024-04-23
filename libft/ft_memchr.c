/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:16:38 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:16:39 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	find;

	string = (unsigned char *)s;
	find = (unsigned char)c;
	while (n--)
	{
		if (*string++ == find)
		{
			return ((void *)--string);
		}
	}
	return (0);
}

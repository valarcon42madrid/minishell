/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:51:11 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:51:12 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	unsigned int	c;

	c = 0;
	while (c < len)
	{
		if (src[c])
		{
			dst[c] = src[c];
			c++;
		}
		else
		{
			while (c < len)
			{
				dst[c] = '\0';
				c++;
			}
			return (dst);
		}
	}
	return (dst);
}

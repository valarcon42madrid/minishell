/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:48:44 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:48:45 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	dlen;

	if (!dstsize)
		return (ft_strlen(src));
	index = 0;
	dlen = ft_strlen(dst);
	if (dstsize > dlen)
	{
		while (src[index] && (dlen + index < dstsize - 1))
		{
			dst[dlen + index] = src[index];
			index++;
		}
		dst[dlen + index] = 0;
		return (dlen + ft_strlen(src));
	}
	return (dstsize + ft_strlen(src));
}

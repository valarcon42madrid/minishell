/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:17:56 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:18:12 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dp;
	unsigned const char	*sp;
	size_t				index;

	dp = (unsigned char *)dst;
	sp = (unsigned const char *)src;
	index = 0;
	if (!dst && !src)
		return (0);
	if ((dst || src) && len)
	{
		if (dp > sp)
		{
			while (++index <= len)
				dp[len - index] = sp[len - index];
		}
		else
		{
			while (len--)
				*dp++ = *sp++;
		}
	}
	return (dst);
}

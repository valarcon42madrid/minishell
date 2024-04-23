/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:52:28 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:52:32 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hcount;
	size_t	nlen;

	hcount = 0;
	nlen = ft_strlen(needle);
	if (!nlen)
		return ((char *)haystack);
	if (!len)
		return (0);
	while ((haystack[hcount] && len))
	{
		if (!(ft_strncmp(&haystack[hcount], needle, nlen)))
			return ((char *)&haystack[hcount]);
		if (nlen > len)
			return (0);
		hcount++;
		len--;
	}
	return (0);
}

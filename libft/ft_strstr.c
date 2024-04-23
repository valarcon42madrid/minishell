/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:53:08 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:53:09 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	hcount;
	size_t	nlen;

	hcount = 0;
	nlen = ft_strlen(needle);
	if (!ft_strncmp(needle, "", 1))
		return ((char *)haystack);
	while (haystack[hcount])
	{
		if (!ft_strncmp(&haystack[hcount], needle, nlen))
			return ((char *)&haystack[hcount]);
		hcount++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:52:48 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:52:50 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	ch;

	len = ft_strlen(s);
	ch = (char)c;
	if (!*s && !c)
		return ((char *)&s[len]);
	if (!*s)
		return (0);
	if (!c)
		return ((char *)&s[len]);
	while (len > 0)
	{
		if (s[len - 1] == ch)
			return ((char *)&s[len - 1]);
		len--;
	}
	return (0);
}

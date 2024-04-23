/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:49:31 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:49:32 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	len;
	size_t	count;
	char	*str;

	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	str = malloc(len + 1);
	if (!str)
		return (0);
	count = 0;
	if (s && f)
	{
		while (count < len)
		{
			str[count] = (*f)(s[count]);
			count++;
		}
		str[count] = 0;
	}
	return (str);
}

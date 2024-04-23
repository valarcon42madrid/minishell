/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:48:29 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:48:30 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		cont;
	int		len;

	cont = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * len + 1);
	if (!dst)
		return (0);
	while (cont < (int)ft_strlen(s1))
	{
		dst[cont] = s1[cont];
		cont++;
	}
	while (cont < len)
	{
		dst[cont] = s2[cont - ft_strlen(s1)];
		cont++;
	}
	dst[len] = 0;
	return (dst);
}

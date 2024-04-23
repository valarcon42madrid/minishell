/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:49:58 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:49:59 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	count;

	len = ft_strlen(s1);
	count = 0;
	while ((count < n) && s2[count])
	{
		s1[len + count] = s2[count];
		count++;
	}
	s1[len + count] = 0;
	return (s1);
}

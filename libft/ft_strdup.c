/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:46:37 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:46:39 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;

	len = ft_strlen(s1);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
		return (0);
	ft_memcpy(copy, s1, len);
	copy[len] = 0;
	return (copy);
}

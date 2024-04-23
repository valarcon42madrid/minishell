/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:56:47 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/22 16:56:50 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned, char *))
{
	size_t	len;
	size_t	count;

	if (!s || !f)
		return ;
	len = ft_strlen(s);
	count = 0;
	if (f && s)
	{
		while (count < len)
		{
			(*f)(count, &s[count]);
			count++;
		}
	}
}

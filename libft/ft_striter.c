/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:47:33 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:47:34 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
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
			(*f)(&s[count]);
			count++;
		}
	}
}

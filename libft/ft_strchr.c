/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:21:41 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:21:43 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*pointer;

	pointer = (char *)s;
	while (*pointer != 0)
	{
		if (*pointer == c)
			return (pointer);
		pointer++;
	}
	if (c == 0)
		return (pointer);
	return (0);
}

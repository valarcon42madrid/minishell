/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:19:34 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:19:35 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	*sp;

	sp = s;
	if (s != (void *)0)
	{
		while (*sp)
		{
			ft_putchar_fd(*sp, fd);
			sp++;
		}
		ft_putchar_fd('\n', fd);
	}
}

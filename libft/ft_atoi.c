/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:12:03 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:12:05 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int						sign;
	unsigned long long int	result;

	sign = 1;
	result = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (ft_isdigit(*str) && *str)
	{
		result = result * 10 + *str - '0';
		str++;
		if (result > 9223372036854775807)
		{
			if (sign < 0)
				return (0);
			return (-1);
		}
	}
	return (sign * result);
}

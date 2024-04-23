/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:15:51 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:15:53 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*nl;

	nl = (t_list *)malloc(sizeof(t_list));
	if (!nl)
		return (0);
	nl->content = (void *)content;
	nl->next = 0;
	return (nl);
}

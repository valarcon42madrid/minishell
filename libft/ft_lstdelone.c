/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:15:09 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:15:11 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst, void *content)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *lst;
	prev = *lst;
	if (tmp && (!ft_strcmp((char *)tmp->content, (char *)content)))
	{
		*lst = tmp->next;
		free(tmp->content);
		free(tmp);
		return ;
	}
	while (tmp && ft_strcmp((char *)tmp->content, (char *)content))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	free(tmp->content);
	free(tmp);
}
